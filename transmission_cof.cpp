float rad2deg(float angle){
	return angle / 180 * TMath::Pi();
}

void transmission_cof() {
	// ---------------
	// TRANSMISSION COEFFICIENTS
	// ---------------
	std::unique_ptr<TFile> file1( TFile::Open("transmission/tc_gamma2.0.root", "READ") );
	TH2F* hist = (TH2F*)file1->Get("tc");

	// ---------------
	// MC EVENTS
	// ---------------
	std::unique_ptr<TFile> file( TFile::Open("simulated_events.root") );
	auto eventsTuple = file->Get<TNtuple>("ntuple");
	
	// disable all the branches
	eventsTuple->SetBranchStatus("*", false);
	// enable the needed branches
	eventsTuple->SetBranchStatus("fPrimaryParticleEnergy", true);
	eventsTuple->SetBranchStatus("fZenithMC", true);
	
	// set the needed variables
	float energy;
	eventsTuple->SetBranchAddress("fPrimaryParticleEnergy", &energy);
	float angle;
	eventsTuple->SetBranchAddress("fZenithMC", &angle); 
	
	auto nEntries = eventsTuple->GetEntries();
	
	// ---------------
	// ADD TRANSMISSION COEFFICIENTS	
	// ---------------
	for (int iEntry = 0; iEntry < nEntries; ++iEntry) {
   		// load data for the given tree entry
   		eventsTuple->GetEntry(iEntry);
   		
   		printf("%f\n", hist->GetBinContent(log10(energy), rad2deg(angle)));
   	}

}
