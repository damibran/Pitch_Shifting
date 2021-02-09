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

    int numChannel = inputAudio.getNumChannels();
    int numSamples = inputAudio.getNumSamplesPerChannel();

    inputAudio.printSummary();

    outputAudio.setBitDepth(inputAudio.getBitDepth());
    outputAudio.setSampleRate(inputAudio.getSampleRate());

    outputBuffer.resize(numChannel);
    for (int i = 0; i < numChannel; ++i)
        outputBuffer[i].resize(numSamples);
}

//Just fft and scaling
void Shifter::make_shift(std::string outputFileName, float factor)
{
    int numChannel = inputAudio.getNumChannels();
    int numSamples = inputAudio.getNumSamplesPerChannel();

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

            scale_spector(factor, inputSpectr, outputSpectr);

            fftw_execute(backward);
            for (int j = 0; j < (int)frame.size(); ++j)
                frame[j] = frame[j] / N;
            std::copy(frame.begin(),frame.end(),outputBuffer[i].begin()+processed_samples);
            processed_samples += N;
        }
        if (numSamples != processed_samples)
        {
            for(int j=0;j<N;j++)
                frame[j]=0;

            std::copy(inputAudio.samples[i].begin() + processed_samples,
                      inputAudio.samples[i].end(),
                      frame.begin());

            fftw_execute(forward);

            scale_spector(factor, inputSpectr, outputSpectr);

            fftw_execute(backward);
            for (int j = 0; j < (int)frame.size(); ++j)
                frame[j] = frame[j] / N;
            std::copy(frame.begin(), frame.begin() + numSamples % N, outputBuffer[i].begin() + processed_samples);
        }
    }

    if (outputAudio.setAudioBuffer(outputBuffer))
    {
        outputAudio.save(outputFileName);
        qDebug() << "OK";
    }
}

void Shifter::shift_to_freq(float freq)
{
    int freq_index=find_freq_index_in_spectre(freq);
    int max_index;

    int numChannel = inputAudio.getNumChannels();
    int numSamples = inputAudio.getNumSamplesPerChannel();

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

                scale_spector(freq_index/max_index, inputSpectr, outputSpectr);

                fftw_execute(backward);
                for (int j = 0; j < (int)frame.size(); ++j)
                    frame[j] = frame[j] / N;
                std::copy(frame.begin(),frame.end(),outputBuffer[i].begin()+processed_samples);
                processed_samples += N;
            }
    }
}

int Shifter::find_max_frame_freq_index(fftw_complex *frame)
{
    float max=0;
    int max_index;
    float abs;
    for (int i=0;i<N;++i )
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

int Shifter::find_freq_index_in_spectre(float freq)
{

}

Shifter::~Shifter()
{
    if(forward)fftw_destroy_plan(forward);
    if(backward)fftw_destroy_plan(backward);
    fftw_free(outputSpectr);
    fftw_free(inputSpectr);
}

void Shifter::make_window(std::vector<double> buffer)
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
