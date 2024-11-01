# Pacman
Checkout this git repository: https://github.com/AdriaanMusschoot/Amugen to find the engine submodule and more of an explanation on how to use the engine.
The game I made is pacman so I modified the engine to work easier for me.

# Details
First change I made in my engine, is that I display images centered, this make it a lot easier to reason about positioning and collision.
The collision itself was then also rather simple: a distance check. It is all that is needed for pacman.
In most cases of my pacman game the collision implementation was forwarded to a finite state machine component, which would handle the collision in the appropriate state, mostly changing the state or destroying a gameobject.

The subject/observer was also really usefull to have all components communicate with eachohter without intertwining to much.
For example the animation components are always listening to the finite state machine component of their respective ghost/pacman to see if they need a different area of the sprite sheet. 
The finite state machine component of the ghost is registered as an observer to the pacman collider, so when pacman collides with a big pickup the ghosts now that they need to change into their blue scared state.

An issue I ran into is that the eating sound of pacman didn't perfectly loop upon eating one of the pick ups. So I modified the soundeffect class of the engine so that I could pause and play.
If pacman then hasn't eaten after a while it will stop making the soundeffect and start playing it again once it picks up another one.

The game is not yet finished but its main goal was to prove that 'Amugen' the game engine worked.
