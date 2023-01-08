#include "GlobalEventType.h"

const char* ToString(GlobalEventType evt) {
	switch (evt)
	{	
	case GlobalEventType::PopulationGrowth:
		return "PopulationGrowth";
	case GlobalEventType::SaviorOfGreece:
		return "SaviorOfGreece";
	case GlobalEventType::InventionOfTheTrireme:
		return "InventionOfTheTrireme";
	case GlobalEventType::Conscription:
		return "Conscription";
	case GlobalEventType::MilitarySuperiority:
		return "MilitarySuperiority";
	case GlobalEventType::RiseOfPersia:
		return "RiseOfPersia";
	case GlobalEventType::Prosperity:
		return "Prosperity";
	case GlobalEventType::DeliveriesFromLydia:
		return "DeliveriesFromLydia";
	case GlobalEventType::Hostilities:
		return "Hostilities";
	case GlobalEventType::ThirtyTyrants:
		return "ThirtyTyrants";
	case GlobalEventType::PlagueOfAthens:
		return "PlagueOfAthens";
	case GlobalEventType::DelphicOracle:
		return "DelphicOracle";
	case GlobalEventType::Drought:
		return "Drought";
	case GlobalEventType::EleusinianMysteries:
		return "EleusinianMysteries";
	case GlobalEventType::TheBirthOfTheAcademy:
		return "TheBirthOfTheAcademy";
	case GlobalEventType::MilitaryCampaignAgainstPersia:
		return "MilitaryCampaignAgainstPersia";
	default:
		return "unknown";
	}
}