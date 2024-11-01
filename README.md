Checkout the git repository: https://github.com/AdriaanMusschoot/Amugen to find the engine submodule and more of an explanation on how to use the engine.

The game I made is pacman so I modified the engine to work easier for me.

First change I made in my engine, is that I display images centered, this make it a lot easier to reason about positioning and collision.
The collision itself was then also rather simple: a distance check. It is all that is needed for pacman.
It requires an instant response of the collision components.

To create an update loop I worked w/ one scene that references one from a vector, this way only one scene is updated and rendered at the time. 
This allows me to easily switch between existing scene without loading a whole new scene everytime.

For the game clock, the renderer and the input manager and gameclock are a Singleton.

The input manager is not linked to any scenes and simply executes a command on either the gamestate or a specific game object

Sound is done through a service locator, which was helpfull as I noticed some short comings while creating the game and after upgrading the soundsystem, all could remain through the service locator

All loading for resource from the resource manager are stored in an RAII wrapper to maintain object so that this doesn't have to be loaded again and again

The most prevelant form of communicating between gameobjects and components is the subject and observer pattern

For example the animation components are always listening to the fsm of their respective ghost/pacman

The response of all the colliders is mostly forward to their respective fsm to handle it
