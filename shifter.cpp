#include "shifter.h"
#define M_PI 3.14159265358979323846 /* pi */
#include <math.h>
#include <QDebug>

Shifter::Shifter()
{
    note_freqs.resize(60);
    note_freqs[0]=65.4063913251496587;
    for(int i =1;i<60;++i)
        note_freqs[i]=note_freqs[i-1]*pow(2.0,1.0/12.0);

    frame.resize(N);
    inputSpectr = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (N / 2 + 1));
    outputSpectr = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * (N / 2 + 1));
    forward = fftw_plan_dft_r2c_1d(N, frame.data(), inputSpectr, FFTW_MEASURE);
    backward = fftw_plan_dft_c2r_1d(N, outputSpectr, frame.data(), FFTW_ESTIMATE);
}

//Loading input file and configuring output file buffer size
void Shifter::load_input_file(std::string inputFileName)
{
    inputAudio.load(inputFileName);

    int numSamples = inputAudio.getNumSamplesPerChannel();

    inputAudio.setNumSamplesPerChannel(numSamples+N-numSamples%N);

    int numChannel = inputAudio.getNumChannels();
    numSamples = inputAudio.getNumSamplesPerChannel();

    inputAudio.printSummary();

    outputAudio.setBitDepth(inputAudio.getBitDepth());
    outputAudio.setSampleRate(inputAudio.getSampleRate());

    outputBuffer.resize(numChannel);
    for (int i = 0; i < numChannel; ++i)
        outputBuffer[i].resize(numSamples,0);
}

std::vector<std::string> Shifter::create_pianoRoll_notes(std::string outputDir)
{
    std::vector<std::string> outputfileNames;
    std::string freq;

    for(int i=0;i<60;++i)
    {
        freq=std::to_string(floor(note_freqs[i]));
        shift_to_freq(note_freqs[i],outputDir+freq+".wav");
        outputfileNames.push_back(freq+".wav");
    }

    return outputfileNames;
}

void Shifter::shift_to_freq(float freq,std::string outputFileName)
{
    int freq_index= round(freq*N/inputAudio.getSampleRate());
    int max_index;

    int numChannel = inputAudio.getNumChannels();
    int numSamples = inputAudio.getNumSamplesPerChannel();

    int hop=N/2;
    int processed_samples;
    for (int i = 0; i < numChannel; ++i)
    {
        processed_samples = 0;
        while (numSamples - processed_samples >= N)
        {
            std::copy(inputAudio.samples[i].begin() + processed_samples,
                      inputAudio.samples[i].begin() + processed_samples + N,
                      frame.begin());

            fftw_execute(forward);

            max_index=find_max_frame_freq_index(inputSpectr);

            scale_spector((float)freq_index/max_index, inputSpectr, outputSpectr);

            fftw_complex t;
            t[0]=cos(hop*(max_index-freq_index));
            t[1]=sin(hop*(max_index-freq_index));
            for(int j=0;j<N/2+1;++j)
            {
                outputSpectr[j][0]=outputSpectr[j][0]*t[0]-outputSpectr[j][1]*t[1];
                outputSpectr[j][1]=outputSpectr[j][0]*t[1]+outputSpectr[j][1]*t[0];
            }

            fftw_execute(backward);

            make_window(frame);

            for (int j = 0; j < (int)frame.size(); ++j)
                frame[j] = frame[j] / N;
            //std::copy(frame.begin(),frame.end(),outputBuffer[i].begin()+processed_samples);
            for(int j=0;j<N;++j)
            {
                outputBuffer[i][j+processed_samples]+=frame[j];
            }
            processed_samples += hop;
        }        
    }

    if (outputAudio.setAudioBuffer(outputBuffer))
    {
        outputAudio.save(outputFileName);
        qDebug() << "OK";
    }
}

int Shifter::find_max_frame_freq_index(fftw_complex *frame)
{
    float max=0;
    int max_index;
    float abs;
    for (int i=0;i<N/2+1;++i )
    {
        abs=sqrt(frame[i][0]*frame[i][0]+frame[i][1]*frame[i][1]);
        if(abs>max)
        {
            max=abs;
            max_index=i;
        }
    }
    return max_index;
}

Shifter::~Shifter()
{
    if(forward)fftw_destroy_plan(forward);
    if(backward)fftw_destroy_plan(backward);
    fftw_free(outputSpectr);
    fftw_free(inputSpectr);
}

void Shifter::make_window(std::vector<double>& buffer)
{
    for (int k = 0; k < N; ++k)
    {
        buffer[k] = (0.54 - 0.46 * cos((2 * M_PI * k) / N)) * buffer[k];
        //buffer[k] = (0.355768 - 0.487396 * cos((2 * M_PI * k) / N) + 0.144232 * cos((4 * M_PI * k) / N) - 0.012604 * cos((6 * M_PI * k) / N))* buffer[k];
    }
}

void Shifter::scale_spector(float factor, fftw_complex *inputSpectr, fftw_complex *outputSpectr)
{

    for (int i = 0; i < N / 2 + 1; ++i)
    {
        outputSpectr[i][0] = 0;
        outputSpectr[i][1] = 0;
    }

    for (int i = 0; i < N / 2 + 1; ++i)
    {
        if (i * factor > 0 && i * factor < N / 2 + 1)
        {
            outputSpectr[(int)(i * factor)][0] = inputSpectr[i][0];
            outputSpectr[(int)(i * factor)][1] = inputSpectr[i][1];
            //std::cout << (int)(i * factor) << " : " << i<<"\n";
        }
    }
}
