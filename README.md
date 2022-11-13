# Beyond Standard Model Graph Neural Network Samples
The purpose of this repository is to create ROOT samples from TopQ derivations containing traceable information about the (truth) jet's origin. 
This information is particularly important when training a Graph Neural Network because, training a Multi-Layer-Perceptron requires truth flags, i.e. whether any given (truth) jet is truly from a top-quark decay or not. 

## Running the Code
- If you have not previously used AnalysisTop, you need to follow this guide closely; 
[Link to AnalysisTop Tutorial - See Section 1. First time setup of AnalysisTop](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/TopxAODStartGuideR21#1_First_time_setup_of_AnalysisTo)
- Once AnalysisTop is installed, clone this repository;
```
git clone ssh://git@gitlab.cern.ch:7999/hqt-bsm-4tops/bsm4tops-gnn-ntuples.git
``` 
- Followed by; 
```bash
source setup.sh
```
- Once compiled, navigate to the `EventSelection` folder and select the desired configuration file for the derivation sample. Alternatively, new configuration files can be dumped using the ```bash python WriteConfig.py ``` script. 

## Some Other Useful Scripts
- Scripts contained within the `MultiProcessing` folder are reserved for Grid submissions or local multithreading jobs.
To run locally, modify the `MakeConfigs.py` script as needed (i.e. output/inputs) and execute the `Running.sh` to start the process. 
If Grid jobs need to be submitted in bulk, simply naviate into the 'Grid' folder and do ```python Build.py``` followed by ```python 01SubmitToGrid.py```. NOTE: Make sure to run ```bash lsetup panda``` before submitting jobs to the Grid.

## Structure of Output ROOT File
- <particle_name>_pt: The transverse momenta.
- <particle_name>_eta: The pseudo-rapidity.
- <particle_name>_phi: The azimuthal angle within the ATLAS detector.
- <particle_name>_e: The energy.
- <particle_name>_charge: The charge as per the simulation/reconstruction in AnalysisTop.
- <particle_name>_pdgid: The PDGID [See here for an elaborate PDGID table](https://pdg.lbl.gov/2007/reviews/montecarlorpp.pdf)
- <particle_name>_FromRes: Indicates whether the top-quark originates from a resonance - currently supports scalar Higgs (BSMH) and vector boson Z-prime (ZBSM). 
- <particle_name>_index: The index of the top-quark.
- <particle_name>_TopIndex: The index of the top-quark that the particle has been matched with.
- <particle_name>_ChildIndex: The index of the child that the particle has been matched with (child meaning the FIRST decay products of the top-quark).

## Particle Names
- children: These are the direct decay products of the top-quark. If one of the decay products is a W-boson, the children are used instead.
- top: The top-quark(s) in the sample after gluon radiation i.e. FSR (Final State Radiation).
- truthjet: Simulated jets before adding any detector inefficiencies. 
- truJparton: The partons constituting the truthjet. These are singly matched to individual children (by index) and can be used for debugging the current matching scheme.
- jet: The detector jets.
- Jparton: Partons contributing to the constructed jets. Again these are singly matched to individual children (by index) and can be used for debugging.

## Current Matching Scheme of Tops to (Truth)Jets
- Initially, the generator particles are used to recursively call their children using ```c particle -> child(index); ```.
- If any of those children contain the absolute value of the PDGID of a top, then those are added to a list of tops (```c particle -> pdgId(); ```). 
- Tops within the list are recursively scanned for their children until none of the children contain the top PDGID, i.e. the top has undergone gluon radiation.
- The very last instance of the top-quark (FSR) is then used as the seed, to recursively scan and record the decay chain objects. This is repeated for n-Tops.
- This decay list is subsequently used to find common object addresses within the (truth)jets using the class method; 
```c jet -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons")``` 
- If the parton and decay chain lists share common object addresses, then the (truth)jet is marked with the index of the corresponding top (i.e. `TopIndex`).
