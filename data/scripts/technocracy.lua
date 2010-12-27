-- All the typecodes for objects.
-- MUST CORRESPOND WITH THE C TYPES.
-- ..Unless you want fuckin' neat shit to happen.
generic_object = 0

-- Objects of the scene
o = { }

-- Particle bundles for the scene
par = { }

-- Creates a new scene
NewScene()

-- Particles
par["Shower"] = CreateParticles(0, 0, 0, 0, 2000, 0, 0, 0, "")

-- First object
o["Starship"] = CreateObject(generic_object, 0, 0, 0, "data/spaceship2.png")

-- Isometric platform object
o["Platform"] = CreatePlatform();

--[[
06:29 < ToxicFrog> Right.
06:31 < ToxicFrog> If you wanted methods, you'd either replace that with a fulluserdata (of type int *, or do away with
                   the int entirely if this is the only place it's used and make it an object *), or a lua table with a
                   field holding that int.
06:31 < ToxicFrog> If it's a table, you then simply populate it with methods.
06:31 < ToxicFrog> Eg, objects.model1 = { n = <integer key>, NewAnimation = <NewAnimation function> }
06:32 < ToxicFrog> If it's a userdatum, you construct such a method table and then setmetatable(objects.model1, {
                   __index = <method table> })
--]]