import ROOT as rt
import numpy as np
import matplotlib.pyplot as plt


def modify():
    filename = "simulated_events.root"

    myFile = rt.TFile.Open(filename, "READ")
    myTree = myFile.ntuple

    data = []
    for entry in myTree:
        data.append(np.log10(entry.fPrimaryParticleEnergy))

    return


modify()
