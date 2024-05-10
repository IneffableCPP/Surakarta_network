#ifndef SURAKARTA_AGENT_MINE_H
#define SURAKARTA_AGENT_MINE_H
#include <memory>
#include "surakarta_agent_base.h"

class SurakartaAgentMine : public SurakartaAgentBase {
public:
    using SurakartaAgentBase::SurakartaAgentBase;
    SurakartaMove CalculateMove() override;
};
#endif // SURAKARTA_AGENT_MINE_H
