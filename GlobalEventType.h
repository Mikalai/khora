#pragma once

enum class GlobalEventType {
	Unknown = -1,
	PopulationGrowth,	
	SaviorOfGreece,
	InventionOfTheTrireme,
	Conscription,
	MilitarySuperiority,
	RiseOfPersia,
	Prosperity,
	DeliveriesFromLydia,
	Hostilities,
	ThirtyTyrants,
	PlagueOfAthens,
	DelphicOracle,
	Drought,
	EleusinianMysteries,
	TheBirthOfTheAcademy,	
	MilitaryCampaignAgainstPersia,
	End,
	Count = End
};

const char* ToString(GlobalEventType evt);