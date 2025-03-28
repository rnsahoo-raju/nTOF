#include <TFile.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TF1.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

void analysis() {

    std::string filename1 = "Er166_JENDL_plt_rns.dat";
    std::string filename2 = "Er166_ENDF_plt_rns.dat";

    std::ifstream infile1(filename1);


    std::vector<double> x1, y1, ey1, y11, y21;
    double temp_x1, temp_y1, temp_ey1, temp_y11, temp_y21;

    while (infile1 >> temp_x1 >> temp_y1 >> temp_ey1 >> temp_y11 >> temp_y21) {
        x1.push_back(temp_x1);
        y1.push_back(temp_y1);  // Column 2 for the first y
        ey1.push_back(temp_ey1); // Column 3 for error bars (assuming no error in x)
        y11.push_back(temp_y11); // Column 4 for line plot
        y21.push_back(temp_y21); // Column 5 for red line plot
    }

    std::ifstream infile2(filename2);
    std::vector<double> x2, y2, ey2, y12, y22;
    double temp_x2, temp_y2, temp_ey2, temp_y12, temp_y22;

    // Read the second file
    while (infile2 >> temp_x2 >> temp_y2 >> temp_ey2 >> temp_y12 >> temp_y22) {
        x2.push_back(temp_x2);
        y2.push_back(temp_y2);  // Column 2 for the second y
        ey2.push_back(temp_ey2); // Column 3 for error bars (assuming no error in x)
        y12.push_back(temp_y12); // Column 4 for line plot
        y22.push_back(temp_y22); // Column 5 for red line plot
    }
    
    //Plotting of Canvas1 for JENDL
    TCanvas *c1 = new TCanvas("c1", "Resonances - JENDL", 1200, 800);
    c1->SetGrid();

    TGraphErrors *graph1 = new TGraphErrors(x1.size(), &x1[0], &y1[0], &ey1[0]);
    graph1->SetTitle("JENDL"); graph1->SetMarkerStyle(20); graph1->SetMarkerColor(kBlack);
    graph1->SetLineColor(kBlack); graph1->Draw("AP");

    TGraph *graph11 = new TGraph(x1.size(), &x1[0], &y11[0]);
    graph11->SetLineColor(kBlue); graph11->Draw("L SAME");

    TGraph *graph21 = new TGraph(x1.size(), &x1[0], &y21[0]);
    graph21->SetLineColor(kRed); graph21->Draw("L SAME");

    graph1->GetXaxis()->SetTitle("Resonance Energy (eV)");
    graph1->GetYaxis()->SetTitle("Normalized Yields");
    
    TLegend *legend1 = new TLegend(0.6, 0.8, 0.9, 0.9);
    legend1->AddEntry(graph1, "Column 2 with Errorbars", "p");
    legend1->AddEntry(graph11, "Column 1:4", "l");
    legend1->AddEntry(graph21, "Column 1:5", "l");
    legend1->Draw();

    //Plotting of Canvas1 for ENDF
    TCanvas *c2 = new TCanvas("c2", "Resonances - File 2", 1200, 800);
    c2->SetGrid();

    TGraphErrors *graph2 = new TGraphErrors(x2.size(), &x2[0], &y2[0], &ey2[0]);
    graph2->SetTitle("ENDF"); graph2->SetMarkerStyle(20); graph2->SetMarkerColor(kBlack); 
    graph2->SetLineColor(kBlack); graph2->Draw("AP");

    TGraph *graph12 = new TGraph(x2.size(), &x2[0], &y12[0]);
    graph12->SetLineColor(kBlue); graph12->Draw("L SAME");

    TGraph *graph22 = new TGraph(x2.size(), &x2[0], &y22[0]);
    graph22->SetLineColor(kRed); graph22->Draw("L SAME");

    graph2->GetXaxis()->SetTitle("Resonance Energy (eV)");
    graph2->GetYaxis()->SetTitle("Normalized Yields");
    
    TLegend *legend2 = new TLegend(0.6, 0.8, 0.9, 0.9);
    legend2->AddEntry(graph2, "Column 2 with Errorbars", "p");
    legend2->AddEntry(graph12, "Column 1:4", "l");
    legend2->AddEntry(graph22, "Column 1:5", "l");
    legend2->Draw();
    
    

    //Plotting of Canvas1 for Comparision
    TCanvas *c3 = new TCanvas("c3", "Comparison - File 1 vs File 2", 1200, 800);
    c3->SetGrid();
    
    TGraphErrors *graph3 = new TGraphErrors(x1.size(), &x1[0], &y1[0], &ey1[0]);
    graph3->SetTitle("JENDL & ENDF"); graph3->SetMarkerStyle(20);
    graph3->SetMarkerColor(kBlack); graph3->SetLineColor(kBlack); graph3->Draw("AP SAME");

    TGraph *graph_comp1 = new TGraph(x1.size(), &x1[0], &y21[0]);
    graph_comp1->SetLineColor(kGreen); graph_comp1->Draw("L SAME");

    TGraph *graph_comp2 = new TGraph(x2.size(), &x2[0], &y22[0]);
    graph_comp2->SetLineColor(kPink); graph_comp2->Draw("L SAME");
    
    TLegend *legend3 = new TLegend(0.6, 0.8, 0.9, 0.9);
    legend3->AddEntry(graph3, "Data with Errors", "p");
    legend3->AddEntry(graph_comp1, "JENDL Column-1:5", "l");
    legend3->AddEntry(graph_comp2, "ENDF Column-1:5", "l");
    legend3->Draw();
    
    graph_comp1->GetXaxis()->SetTitle("Resonance Energy (eV)");
    graph_comp1->GetYaxis()->SetTitle("Normalized Yields");
    
    c1->SaveAs("jendl.png");
    c2->SaveAs("endf.png");
    c3->SaveAs("comp_jendl_endf.png");
}

