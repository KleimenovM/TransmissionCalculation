{
	// ---------------
	// TRANSMISSION COEFFICIENTS
	// ---------------
	std::unique_ptr<TFile> file1( TFile::Open("transmission/tc_gamma2.0.root", "READ") );
	TH2F* hist = (TH2F*)file1->Get("tc");

	// ---------------
	// MC EVENTS
	// ---------------
	std::unique_ptr<TFile> file( TFile::Open("simulated_events.root", "UPDATE") );
	auto eventsTuple = file->Get<TNtuple>("ntuple");
	
	// disable all the branches
	eventsTuple->SetBranchStatus("*", false);
	// enable the needed branches
	eventsTuple->SetBranchStatus("fPrimaryParticleEnergy", true);
	eventsTuple->SetBranchStatus("fZenithMC", true);
	
	// set the needed variables
	Float_t energy;
	eventsTuple->SetBranchAddress("fPrimaryParticleEnergy", &energy);
	Float_t angle;
	eventsTuple->SetBranchAddress("fZenithMC", &angle); 

	Float_t new_v;
	auto newBranch = eventsTuple->Branch("new_v", &new_v, "new_v/F");
	
	Long64_t nEntries = eventsTuple->GetEntries();
	
	// ---------------
	// ADD TRANSMISSION COEFFICIENTS	
	// ---------------
	for (Long64_t iEntry = 0; iEntry < nEntries; ++iEntry) {
   		// load data for the given tree entry
   		eventsTuple->GetEntry(iEntry);
   		
   		auto lgE = log10(energy);
   		
   		// if neutrino comes from the "top" or has very low energy
   		if (angle < 90 || lgE < 3){ new_v = 1.0; }
   		// if neutrino has extremely high energy
   		else if (lgE > 10){ new_v = 0.0; }
   		else
   		{	
			auto iBin = hist->FindBin(lgE, angle);
			new_v = hist->GetBinContent(iBin);  			
		}

		newBranch->Fill();
   	}
   	
   	eventsTuple->Write("", TObject::kOverwrite); // save only the new version of the tree
   		
}
