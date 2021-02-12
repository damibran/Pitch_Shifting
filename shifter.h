#ifndef SHIFTER_H
#define SHIFTER_H

#include <vector>
#include<map>
#include <fftw3.h>
#include <AudioFile.h>

class Shifter
{
public:
    Shifter();
    ~Shifter();
    std::vector<double> note_freqs;
    void load_input_file(std::string inputFileName);
    std::vector<std::string> create_pianoRoll_notes(std::string outputDir);
private:
    void shift_to_freq(float freq, std::string outputFileName);
    int find_max_frame_freq_index(fftw_complex *frame_spectr);
    void make_window(std::vector<double> buffer);
    void scale_spector(float factor, fftw_complex *inputSpectr, fftw_complex *outputSpectr);
private:
    const int N = 4096;
    AudioFile<double> inputAudio;
    std::vector<double> frame;
    AudioFile<double> outputAudio;
    AudioFile<double>::AudioBuffer outputBuffer;
    fftw_complex *inputSpectr;
    fftw_complex *outputSpectr;
    fftw_plan forward;
    fftw_plan backward;
};

#endif // SHIFTER_H
