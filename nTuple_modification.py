import ROOT as rt
import numpy as np
import matplotlib.pyplot as plt


def modify():
    # EVENTS
    filename1 = "simulated_events.root"

    myFile = rt.TFile.Open(filename1, "READ")
    myTree = myFile.ntuple
    n = myTree.GetEntries()

    angles, energy = np.zeros(n), np.zeros(n)
    for i, entry in enumerate(myTree):
        energy[i] = np.log10(entry.fPrimaryParticleEnergy)
        angles[i] = entry.fZenithMC

    # TRANSMISSION
    filename2 = "transmission/tc_gamma2.0.root"
    file2 = rt.TFile.Open(filename2, "READ")
    myHist = file2.Get("tc")

    m, k = 199, 179
    angles0 = np.linspace(90, 180, k)
    energies0 = np.linspace(3, 10, m)
    tc = np.zeros([m, k])

    for i, e in enumerate(energies0):
        for j, a in enumerate(angles0):
            tc[i, j] = myHist.GetBinContent(i + 1, j + 1)

    # DRAWING
    fig, ax1 = plt.subplots(figsize=(10, 6))
    ax1.pcolor(tc.T, cmap='autumn')

    ax2 = ax1.twinx()
    ax2.scatter((energy - 3) * 200 / 7, angles, s=1, color='black', alpha=.05)
    plt.ylim(90, 180)
    plt.xlabel("lg(E/GeV)")
    plt.xticks(np.linspace(0, 200, 8), np.arange(3, 11, 1))

    plt.show()

    return


modify()
