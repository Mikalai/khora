#pragma once

#include <Resources.h>
#include <array>
#include <Effects/PolicyEffect.h>

class PolicyTemplate {
public:
	PolicyTemplate(Policies policy, PolicyEffect& effect, PolicyType type);

    const PolicyEffect& GetEffect() const;
	Policies GetType() const;
	
	const std::string& GetName() const;
	const std::string& GetDescription() const;

private:
	Policies policy{ Policies::policy_unknown };    
	PolicyEffect* effect;
	PolicyType type;
};

const PolicyTemplate& GetPolicyTemplate(Policies policy);