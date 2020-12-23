
# Plan:

 - [x] Level intro
 - [ ] Setup system to define a level
    - [x] Setup enemy spawning system
    - [ ] Clean up enemy spawning system
    - [ ] Setup death scenario
    - [ ] Setup win scenario
 - [ ] Create first level


## Enemies:

 - __Simple:__ Stationary, keeps firing targeted at you

- __Chaser:__ Chases you and keeps firing

- __Charger:__ Chases you, until it's in some distance, then it charges at you. If it hits you, you take a lot of damage. If it hits a wall it's destroyed

- __Suicide:__ Chases you, if it gets into distance it explodes

- __Rocketeer:__ Fires rockets at you. Stationary

- __Ufo:__ Keeps firing, spins around and moves around



# Spawn enemy (movement):
_Note_: Implement this in `Enemy.h`

- Create entity outside map with following components
 - Transform
 - Sprite
 - Movement
 - Target
 - Health (invulnerable)
 - Attack behavior (disabled)

- Set target component to "spawn" point (the point it moves to) 

- When target is reached:
 - Remove target component
 - Enable attack behavior
 - Enable life
 - Call "custom" on-spawn function (for specialized enemies)      


Level data:

    Reward (for later)
    
    On start
    
    On update
    
    Create enemy
    
    Boolean to signal that spawning has finished
    
    Function to spawn enemy (it moves into the scene)

