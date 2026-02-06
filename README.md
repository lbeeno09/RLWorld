# RLWorld
Unreal map for my Master's Thesis

## Leaning Agents Flow

- Manager (Manages Agens w/ ID)
	- Policy
		- Run Inference
	- PPO Trainer
		- Run Training

- Interactor (Exchanges with Manager's Policy and Manager's PPO Trainer)
	- Specify Observation
	- Gather Observation
	- Specify Actions
	- Perform Actions

- Training Environment (Exchanges with Manager's PPO Trainer)
	- Gather Rewards
	- Gather Completions
	- Reset Episode

All the overriding methods in Interactor and Training Environment are unique to applications