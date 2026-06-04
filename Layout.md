# MARL　Structure 

This markdown file shows how the MARL Environment is setup.

## Pursuer's Setup

This project learns the pursuer's side with Multi-Agent Reinforcement Learning(MARL) and try to capture the Evader before it reaching the goal.

- Character: The physical actor
- AI Controller: controls the character. Receives the movement decisions from RL Manager
- 


## Evader's Setup

This project makes use of the traditional tree for the Evader's side so that the RL is purely focuesed on the pursuers' learning on their actions. 

- Character: The physical actor
- AI Controller: controls the character. runs the Behavior Tree(BT) and handles EQS queries
- Environment Query Context: EQC class to provide EQS the location of Pursuers to run away from them