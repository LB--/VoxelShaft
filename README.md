Recipe Spelunker
================

_"You mine, you craft, and you use plugins, but you certainly don't call it 'caving'."_

Plain and simple, this is a clone of Minecraft. I am very familiar with the mechanics of Minecraft but I am not happy with the implementation. No, I don't hate Java - on the contrary I think it's really cool. I just prefer C++.

## Project Goals
This will be completely plugin-based, to the point of vanlla behavior being an optional plugin. Obviously this system isn't as easy in C++ as it is in Java, as there's no reflection or any mechanisms to ensure compatibility, but I'll find a way to make it work. Unfortunately I'll not be able to use anything from C++'s standard library without running into compatibility problems. I'll also have to be concious of padding. You can be concious of my mistakes.

The goal is to make the vanilla behavior closely remeble that of Minecraft, but have an emphasis on installing community-made plugins (if such a community exists). I'm intentionally setting impossible expectations because I want to see what I can do.

Current target goal: inter/intra-dimensional portals that you can see through and walk through, like _real_ portals, not that mystery stuff in Minecraft.
