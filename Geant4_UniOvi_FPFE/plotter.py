
import ROOT as r

# Open rootfile
f = r.TFile.Open("YourApplication.root")

# Get the directory as a tree
t = f.Get("histograms")

# Get the histograms
edep = t.Get("Edep")
trackL = t.Get("trackL")

# Create a Canvas
c = r.TCanvas("c", "", 20, 20, 1000, 1000)

c.Divide(1, 2) 

c.cd(1)
edep.Draw("hist")

c.cd(2)
trackL.Draw("hist")


c.Print("mi_histograma.png", "png")

out = r.TFile("./fileConMiHistograma.root", "recreate")
c.Write()
