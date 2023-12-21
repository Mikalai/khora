#pragma once

#include <Resources.h>
#include <array>
#include <Effects/PolicyEffect.h>

class PolicyTemplate {
public:
    PolicyTemplate(PoliciesType policy, PolicyEffect& effect, PolicyType type);

    const PolicyEffect& GetEffect() const;
    PoliciesType GetType() const;
	
	const std::string& GetName() const;
	const std::string& GetDescription() const;

private:
    PoliciesType policy{ PoliciesType::policy_unknown };    
	PolicyEffect* effect;
	PolicyType type;
};

const PolicyTemplate& GetPolicyTemplate(PoliciesType policy);