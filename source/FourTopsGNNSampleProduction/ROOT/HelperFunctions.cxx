#include "FourTopsGNNSampleProduction/HelperFunctions.h"

std::vector<Truth_> UniqueObject(std::vector<Truth_> Particles)
{
	std::vector<Truth_> Out;
  	for (Truth_ T : Particles)
  	{
    		if (!(std::find(Out.begin(), Out.end(), T) != Out.end())){ Out.push_back(T); }
  	}
  	return Out; 
}

Truth_ GetDecayTip(Truth_ part, std::vector<Truth_> inpt)
{
  	for (unsigned int i(0); i < part -> nChildren(); i++)
  	{
    		Truth_ c = part -> child(i); 
    		if (!c){ continue; }
    		if (std::find(inpt.begin(), inpt.end(), c) != inpt.end())
		{ 
			return GetDecayTip(c, inpt); 	
		}
  	}
  	return part;
}

std::vector<Truth_> Intersection(std::vector<Truth_> V1, std::vector<Truth_> V2)
{
	std::vector<Truth_> TMP; 
	for (Truth_ t_c : V1)
	{
		for (Truth_ t_p : V2)
    		{
			if (t_c != t_p){continue;}
      			TMP.push_back(t_c); 
			break;
    		}
  	}
  	TMP = UniqueObject(TMP); 
  
  	// Check that the decay chain is unique and aim to get the tip of the decay
  	std::vector<Truth_> output; 
  	for (Truth_ c : TMP)
  	{ 
    		Truth_ c1 = GetDecayTip(c, TMP); 
    		if (c1 != c){ continue; }
		output.push_back(c1);
  	}
  	return output;
}

int FindObject(Truth_ obj, std::vector<Truth_> V1)
{
	int index = -1; 
  	for (unsigned int i(0); i < V1.size(); i++)
  	{
    		if (V1.at(i) != obj){ continue; }
		index = i; 
		break; 
  	}
  	return index; 
}

void MatchingJets(
	std::vector<Truth_> Children, JetC_ JContainer, 
	_ivec c_index, _ivec j_index, // External index mapping
	__ivec* jpc_index, _ivec* jp_index, _ivec* jp_jindex, 
	_fvec* pt, _fvec* eta, _fvec* phi, _fvec* e, _fvec* charge, _fvec* pdgid)
{
	std::vector<Truth_> Added; 
	for (unsigned int ci(0); ci < Children.size(); ++ci)
	{
		Truth_ child = Children[ci]; 
      		std::vector<Truth_> Chain; 
      		ParticleID::GetDecayPath(child, &Chain); 
      		for (unsigned int j(0); j < JContainer -> size(); ++j)
      		{
         		Jet_ jet = JContainer -> at(j); 
         		std::vector<Truth_> partons = jet -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons"); 
         		std::vector<Truth_> mutual = Intersection(Chain, partons); 
         		if (mutual.size() == 0){continue;}
         		for (Truth_ p : mutual)
         		{
            			int index = FindObject(p, Added); 
            			if (index != -1)
				{ 
					(*jpc_index)[index].push_back(c_index[ci]); 
					continue;
				}
            
            			Added.push_back(p); 
            			index = Added.size()-1; // the -1 is there on purpose to make it consistent with indexing
            			jp_index -> push_back(index); 
            			jp_jindex -> push_back(j_index[j]); 
            
            			pt -> push_back(p -> pt()); 
            			eta -> push_back(p -> eta()); 
            			phi -> push_back(p -> phi()); 
            			e -> push_back(p -> e()); 
            			
            			pdgid -> push_back(p -> pdgId()); 
            			charge -> push_back(p -> charge());

            			(*jpc_index).push_back({c_index[ci]});
         		}
      		}   
   	}
}

void MatchingJetsToTops(
	std::vector<Truth_> Tops, JetC_ JContainer, 
	__ivec* j_tindex, _ivec* t_index)
{
	for (unsigned int i(0); i < Tops.size(); ++i)
   	{
      		std::vector<Truth_> Chain;
      		Truth_ top = Tops[i]; 
      		ParticleID::GetDecayPath(top, &Chain); 
      		for (unsigned int j(0); j < JContainer -> size(); ++j)
      		{
         		Jet_ jet = JContainer -> at(j); 
	 		std::vector<Truth_> jparton = jet -> getAssociatedObjects<xAOD::TruthParticle>("GhostPartons"); 
         		std::vector<Truth_> mutual = Intersection(Chain, jparton); 
         		if (mutual.size() == 0){ continue; }
	 		if ((*j_tindex)[j][0] == -1){ (*j_tindex)[j][0] = t_index -> at(i); }
	 		else { (*j_tindex)[j].push_back(t_index -> at(i)); }
      		}	
   	}
}
