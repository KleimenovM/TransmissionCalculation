import ROOT as rt


def modify():
    filename = "simulated_events.root"

    file = rt.TFile.Open(filename)

    data = file.Get("ntuple")

    data.Draw("log10(fPrimaryParticleEnergy)")  # log10 (neutrino energy in GeV)

    input("Press any key to quit: ")

    return


modify()
