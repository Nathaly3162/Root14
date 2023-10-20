/*
In this ROOT function we generate a distribution according to v2
between 0 and pi
To run do:
root
.L EG_v2.C
rootfuncgenerate(10000)
*/
// include C++ STL headers
#include <iostream>
#include <fstream>  // Include the fstream header
using namespace std;
// ROOT library obejcts
#include <TF1.h> // 1d function class
#include <TH1.h> // 1d histogram classes
#include <TStyle.h> // style object
#include <TMath.h> // math functions
#include <TCanvas.h> // canvas object

void rootfuncgenerate(Int_t nEvents, Int_t nTracks, Double_t v2) {
    cout << "Generating " << nEvents << " events with " << nTracks << " tracks each" << endl << endl;
    
    // open output file
    ofstream file("phi_dist.dat");

    // Create a histogram to store the generated v2 values
    TH1D* hPhi = new TH1D("hPhi", "Generated v2 distribution; v2; Counts", 100, 0, 6.283);  // 0 to 2π

    // Create a function for the desired distribution
    TF1* v2Func = new TF1("v2Func", "[0] * (1 + 2 * [1] * cos(2 * (x - 0)))", 0, 6.283);  // 0 to 2π
    v2Func->SetParameters(1000000, 0.04957);  // Set parameters based on your desired values

    // Loop over the number of events
    for (Int_t n = 0; n < nEvents; n++) {
        file << "Event " << n << endl;
        file << "nTracks " << nTracks << endl;

        // Generate nTracks v2 values for each event and print them
        Double_t v2Values[nTracks]; // Array to store v2 values
        for (Int_t nt = 0; nt < nTracks; nt++) {
            v2Values[nt] = v2Func->GetRandom();
            file << nt << " : " << v2Values[nt] << endl;
        }

        // Fill the histogram with the generated v2 values
        for (Int_t i = 0; i < nTracks; i++) {
            hPhi->Fill(v2Values[i]);
        }
    }
    
    // Close the output file
    file.close();

    // Set ROOT drawing styles
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(1111);

    // Create a canvas for hPhi
    TCanvas* c2 = new TCanvas("c2", "v2 canvas", 900, 600);
    hPhi->SetMinimum(0);
    hPhi->Draw();

    // Create a 1D function for fitting the generated data
    TF1* fitFunc = new TF1("fitFunc", "[0] * (1 + 2 * [1] * cos(2 * (x - 0)))", 0, 6.283);  // 0 to 2π
    fitFunc->SetParameters(1000000, 0.04957);  // Set parameters based on your desired values
    fitFunc->SetLineColor(kRed);
    hPhi->Fit(fitFunc);

    // Save the canvas as a picture
    c2->SaveAs("v2_rootfunc.jpg");
}

