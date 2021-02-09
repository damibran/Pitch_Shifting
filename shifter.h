#ifndef SHIFTER_H
#define SHIFTER_H

#include <vector>
#include<map>
#include <fftw3.h>
#include <AudioFile.h>

class Shifter
{
public:
    int octave=2;
    std::map<std::string,int> keys {{ "z" , 0 },
                                    { "s" , 1 },
                                    { "x" , 2 },
                                    { "d" , 3 },
                                    { "c" , 4 },
                                    { "v" , 5 },
                                    { "g" , 6 },
                                    { "b" , 7 },
                                    { "h" , 8 },
                                    { "n" , 9 },
                                    { "j" , 10 },
                                    { "m" , 11 }
                                   };
    Shifter();
    ~Shifter();
    std::vector<double> note_freqs;
    void make_shift(std::string outputFileName, float factor);
    void load_input_file(std::string inputFileName);
private:
    const int N = 4096;
    AudioFile<double> inputAudio;
    std::vector<double> tempBuffer;
    AudioFile<double> outputAudio;
    AudioFile<double>::AudioBuffer outputBuffer;
    fftw_complex *inputSpectr;
    fftw_complex *outputSpectr;
    fftw_plan forward;
    fftw_plan backward;
    void make_window(std::vector<double> buffer);
    void scale_spector(float factor, fftw_complex *inputSpectr, fftw_complex *outputSpectr);
};

#endif // SHIFTER_H
