#include <iostream>
#include <math.h>
#include "wav.hpp"
#include <fstream>

using namespace std;

int main(){
	WavSound instrumentSoundChallenge;
	int sampleRate = 44100;
	double dt = 1.0/sampleRate; 
	
	/** Make the duration proportional to the number of lines in the file */
	
	ifstream score;
	string lines;
	score.open("score1.txt");
	int duration = 0;
	while (getline(score, lines)){
		duration ++; // count to get the number of lines of the txt file
	}
	score.close(); // close to prevent errors
	
	int nSamples = duration/dt;
	int waveform[nSamples];
	double amplitude = 0.0;
	int count = 0;
	

	/** Get the frequencies from a file */
	
	score.open("score1.txt"); 
	while (getline(score, lines)){
	double frequency = stof(lines); // change strings to doubles 
	
	/** Iterate to modify the amplitudes of each note */ 
	
	double period = nSamples/duration;
	int c = 0; // to make sure that the amplitude starts at the i max of the previous iteration	
	
	for (int i = 0; i < period; i = i + 1){ 
		
		double time = count * dt; 
		
		if(i <= 0.3 * period){ // 30% of amplitude to be attack stage
			amplitude = (6000/(0.3 * period)) * c; 
			if(i == 0.3 * period){
				c = 0; 
			}
		}
		
		else if(i <= 0.4 * period){ // 10% of amplitude to be decay stage
		amplitude = (-1000/(0.1 * period)) * c + 6000;
			if(i == 0.4 * period){
				c = 0;
			}
		
		}
		
		else if(i <= 0.9 * period){ // 50% of amplitude to be sustain stage
		amplitude = 5000; 
			if(i == 0.9 * period){
				c = 0;
			}		
		
		}
		
		else{ // 10% of amplitude to be release stage 
		amplitude = (-5000/(0.1*period)) * c + 5000;
			if(i == period){
			
			}
		
		}	
	
	//cout << "i:" << i << " amplitude:" << amplitude << endl; - uncomment for debugging
	
	
	c++;	
	
	waveform[count] = amplitude * sin(2*M_PI*frequency*time); //calculate the wave	
		
		count++;
	
		}
	
		

	}
	
	score.close();
	
instrumentSoundChallenge.MakeWavFromInt("Challenge.wav", sampleRate, waveform, nSamples);	
}
	 
	
