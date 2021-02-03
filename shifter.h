#ifndef SHIFTER_H
#define SHIFTER_H

#include <vector>
#include <fftw3.h>
#include <AudioFile.h>

class Shifter
{
public:
    Shifter();
    ~Shifter();
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
