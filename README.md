<div align="center">
<h1>ParticleEx</h1>
<p align="center">
    <img src="https://github.com/user-attachments/assets/f943523f-d7e3-41a9-ac8f-38c06be4cbe6"  alt="logo"/>
</p>
</div>
 
<hr/>

[GTAForums topic](https://gtaforums.com/topic/913903-particleex/)

# Intro
The late 90s and early 2000s were a strange time for hardware and gaming in general, PC as a platform wasn't really established yet, and there were still systems that due to their unique architecture had a bunch of significant advantages, and one of those systems was PlayStation 2.
Thanks to its insane bandwidth and fillrate, developers could achieve things that were unattainable on other platforms without even realizing it, even though the console had a significant drawback of having limited amount of RAM and VRAM.

In the case of GTA 3, this became a key factor that allowed Rockstar Games to afford a massive number of particles on screen.
Steam from pipes and vents on walls, rain, exhaust from car pipes, smoke from a damaged engine, fire and explosion effects.
All of these had a high particle density and looked fantastic, which played a major role in shaping the game's dark atmosphere.

But when it was time to port the game to PC, developers at R* were faced with the fact that the vast majority of GPUs at the time were struggling to handle the incredibly heavy effects and could not provide a stable frame rate, and since the potential PC audience was estimated to be much smaller than the console audience, the decision was made to reduce the quality of particle effects in order to reach as many players as possible.
As a result, significant changes were made to the PC port's code that seriously limited the number and quality of particles, and unfortunately, these changes were permanent with no option to change this in the settings,
because R* didn't want to waste extra resources and instead focused on a faster release on PC and the next game in the series Vice City, which also had an impact.
Since the PC port and Vice City were developed in parallel, some changes never intended for GTA 3 ended up in the game,
and these were not only improvements and optimizations, but also entirely new elements (such as the well known case of helis code being included),
as well as changes or updates to existing elements, which sometimes caused the game to lose what developers had originally planned for it.

Vice City's effects were also downgraded, as R* wanted to leave room for improvements on PS2 and to minimize future issues with the PC port.
But unlike GTA 3, these downgrades were in place from the very beginning, and particle effects were redesigned with them in mind, so they don't look as bad as they do in the PC port of GTA 3.
As a result, effects in the PC port this time are almost identical to PS2 version, aside from a few sprite changes and a slight decrease in the quality of the smoke.


Later, when Microsoft convinced R* to make a graphically enhanced port of both games for the Original Xbox,
the task was given to Rockstar Vienna, and thanks to them and the console's processing power,
GTA 3 received visual enhancements, which included completely new fire and explosion effects, as well as updated other particle effects in general.
But unfortunately, the PC port of the game was used as the base for this, and even though they managed to remove the main limitations in the code, some of the changes and downgrades still remained in the game.
Vice City also received improvements, but unfortunately, only new fire effects were added to it, and the port looks unfinished in general.

Because of all this, ParticleEx was created. The plugin ports particle systems from PS2/Xbox to PC versions of GTA 3/Vice City, and also provides some optional fixes and restores some pre-release content!


# Platform Changes Showcase
This section will list all known changes to particle effects across all platforms. Keep in mind that, although it focuses mainly on what PC version of GTA 3 was missing from the very beginning, ParticleEx restores and ports all these things back into the game.


* ### [III/VC][Xbox/PS2] Smoke
  The biggest downgrade that hit the PC port, causing the game to lose its most essential part.
  
  This affected effects like smoke, steam, dust and exhaust fumes.
  
  The changes touched not only `particle.cfg`, which significantly cut down particles lifespan and maximum range, but also the code, drastically reducing their number by half.
  
  Unfortunately, for the Xbox port, Vienna didn't fully restore everything, but it doesn't look as bad as on PC.

  <img width="800" height="600" alt="smoke" src="https://github.com/user-attachments/assets/d10798dd-fcf2-404c-9439-17d8a7d3512b" />
  
  On PC, this resulted in the game losing its cool details, such as the significant increase in exhaust fumes when you press the gas, or the smoke coming out of Yardie's Lobo door when you get out the car.
    
  <p align="left">
    <img width="800" height="450" alt="1" src="https://github.com/user-attachments/assets/2fbce46d-de8e-4f38-96e5-eea34ee1a86f" />
  </p>
  
  <p align="left">
    <img width="800" height="600" alt="rasta smoke" src="https://github.com/user-attachments/assets/4c91d85c-3dfa-4893-b755-db401921d4b7" />
  </p>
  
  Vice City also suffers from reduced smoke quality on PC, but it's hardly noticeable. As for the Xbox port, unfortunately, Vienna left this aspect the same as on PC.

* ### [III/VC][Xbox/PS2] Particle objects / 2dfx
  Effects that are placed on the map, used for steam from pipes, vents, etc. The game reads them from `2dfx` section of `.ide` files.
  
  On PC this feature, in addition to the previous smoke/steam downgrades, has its own ones, which makes things even worse.
  
  <table>
    <tr>
      <th>
        <img width="800" height="600" alt="pcwall" src="https://github.com/user-attachments/assets/27ce13a7-df3c-4460-a3c6-ed721a06ab24" />
      </th>
      <th>
        <img width="800" height="600" alt="ps2wall" src="https://github.com/user-attachments/assets/e36638d7-0e2d-489f-a951-d1406db8f8aa" />
      </th>
    </tr>
    <tr> 
      <th>
        <img width="800" height="600" alt="pcnoodle" src="https://github.com/user-attachments/assets/36a68dc9-b8b8-45f2-a765-9924a9bf06eb" />
      </th>
      <th>
        <img width="800" height="600" alt="ps2noodle" src="https://github.com/user-attachments/assets/05f4967d-0e29-4e92-a40d-0ac303c15295" />
       </th>
    </tr>
  </table>
  
  Scripts can also create 2dfx, but in this case not many things were changed:
  * The dark smoke effect in Ray's "Silence the Sneak" mission (PC downgrades and Xbox improvements).
  * Fire effects on burning packages in Asuka's "S.A.M." mission (PC downgrades).
  * And some unused fire effects (PC downgrades).

* ### [III][PS2/Xbox] Car/Ped water splash
  This effect appears when you fall into the water while driving or on foot.
  
  Even though this effect lasts for a shorter time on PC, what we're seeing here doesn't seem like a downgrade but an entirely new effect, which is unusual.
  
  However, if we compare this effect to the same one in Vice City, we'll see that it looks very similar, and it’s pretty clear that this is a case of early Vice City code being accidentally ported to the PC version.
  
  <table>
    <th>
      <img width="800" height="600" alt="ps2" src="https://github.com/user-attachments/assets/3c2c9af5-e359-4f6f-9167-bf6b8e135585" />
    </th>
    <th>
      <img width="800" height="600" alt="pc" src="https://github.com/user-attachments/assets/03cb4443-6deb-4d5b-ab1c-c47f291c7d2a" />
    </th>
  </table>
  
  The same goes for the water splashes from cars, the PC version clearly got their code from early VC.
  
  It's also worth mentioning how heavy the effect is on PS2. And also that PS2 code still contains an early, pre-release version of this effect, and the plugin lets you enable it, even though it's less impressive.
  
  Interesting that Vienna changed the effect in the Xbox version, and in fact, it's the same as on PC but more powerful.
  
  <table>
    <th>
      <img width="800" height="600" alt="pc" src="https://github.com/user-attachments/assets/31a687cb-0690-46b8-b8b2-11f783e681f1" />
    </th>
    <th>
      <img width="800" height="600" alt="ps2_s" src="https://github.com/user-attachments/assets/cb821ecd-dd34-492c-a2fc-150d0732269d" />
    </th>
  </table>
  <table>
    <th>
	  <img width="800" height="600" alt="xbox" src="https://github.com/user-attachments/assets/25c98789-7621-49f6-9e71-ca253081e349" />
    </th>
    <th>
      <img width="800" height="600" alt="ps2alt" src="https://github.com/user-attachments/assets/deea86b6-c914-4051-bc7a-985d59aa9994" />
    </th>
  </table>

* ### [III][PS2] Boat splashes
  All the effects a boat creates when it's sailing.
  
  The only particles-related change that clearly looks better on PC compared to PS2. It's hard to say whether this is actually an improvement or just a case of early Vice City code being accidentally leaked to GTA 3 PC, but it's more likely the latter.
  
  <table>
    <th>
      <img width="800" height="600" alt="pc" src="https://github.com/user-attachments/assets/ad2e4aad-a9b5-4c52-a6f2-5a4bddcb1688" />
    </th>
    <th>
      <img width="800" height="600" alt="ps2" src="https://github.com/user-attachments/assets/86c0ec06-2771-4f69-b5db-8a1728239b5a" />
    </th>
  </table>

* ### [III][PS2] Car/Ped puddle splash
  This effect appears when the player (in a vehicle or on foot) interacts with various types of puddles and ponds in the game.
  
  On PC this effect is replaced with a different one, and this is most likely yet another case of Vice City code leak.
  
  <p align="left">
    <img width="800" height="600" alt="rel" src="https://github.com/user-attachments/assets/7204c5fb-0547-4875-b9bf-6882952458fa" />
  </p>

* ### [III][PS2] Foot dust
  When Claude runs and stops too suddenly, a barely noticeable dust effect appears under his feet.
  
  This feature is missing on PC, it was most likely cut to improve performance or due to incompatibility with the smoke downgrades.
  
  <p align="left">
    <img width="800" height="600" alt="dust (5)" src="https://github.com/user-attachments/assets/67891dd5-d38e-4f10-8b30-209da192a962" />
  </p>

* ### [III][PS2] Config file changes
  These changes are restored not by modifying the code, but by using the configuration file from PS2.
  However, it's worth mentioning them because some features barely worked on PC or were significantly downgraded.
  * Dirt particles from wheels. They're supposed to appear when driving off road, but on PC, their lifespan was set too short, making them quite hard to notice.
  * Rain Splashes, raindrops. Most noticeable on cars, on PC these effects disappear almost immediately 
  * Debris particles. They appear during vehicle collisions, explosions, glass breaking, object destruction. Their lifespan was also reduced on PC.
  * Car flame effects. Due to the reduced lifespan on PC, these effects lost their smoothness.
  * All kinds of explosion effects. Due to the downgraded lifespan on PC, these effects disappears faster and are not as smooth as on PS2.

* ### [III/VC][Xbox] Fire on the ground, peds and vehicles
  One of key features of the Xbox port.
  Vienna put a lot of effort into it and added an insane number of sprite frames for this effect.
  Unfortunately, they didn't have enough time to make everything perfect, but it still looks awesome!
  
  <table>
    <th>
      <img width="800" height="600" alt="Screenshot_2026-08-24_00-52-12" src="https://github.com/user-attachments/assets/d039ef48-8d20-4cf3-b509-ccc2af1989e5" />
    </th>
    <th>
      <img width="800" height="600" alt="Screenshot_2026-08-24_00-32-19" src="https://github.com/user-attachments/assets/60bef22f-af61-42d5-aa40-8d80b4e8db24" />
    </th>
  </table>
  
  The plugin fixes one of the original issues that caused the fire from a molotov on the ground to be shifted from the actual center of the fire source.

* ### [III/VC][Xbox] Explosion effects
  Vienna also completely redesigned explosion particles for their port, now they not only have higher resolution but also more frames!
  
  <p align="left">
    <img width="800" height="600" alt="exp (5)" src="https://github.com/user-attachments/assets/f11ab74c-404d-41dc-b131-ddec05eade51" />
  </p>
  
  Unfortunately, this feature remained exclusive to GTA 3, but the plugin changes that and lets you enjoy it in Vice City too!

* ### [III/VC][Xbox] Flamethrower effects
  Since Vienna changed the fire effects on Xbox, they also had to adapt the flamethrower effects as well. Its fire stream now has a different shape and generates twice as many particles as the original!
  
  <p align="left">
    <img width="800" height="600" alt="ft" src="https://github.com/user-attachments/assets/1766f5a6-b419-415a-966e-350e0457e699" />
  </p>

* ### [III/VC][Xbox] Increased hydrant waterspray time
  This change is quite strange. For some reason, Vienna decided to change the time that a broken fire hydrant sprays water, from ***5*** seconds to ***15*** seconds. Well, it's a huge waste of resources in every sense, but we can afford it now.

# Additional features
This section focuses on the optional features that ParticleEx provides. Some of them are fixes and minor changes from other platforms, while others are restored pre-release content that was left broken in the game's code.

* ### [III/VC][PS2/PC] "flame5" bug fix
  R* planned to use different textures for similar types of flame effects, they even added `flame1` and `flame5` textures to the TXD and specified them in the code, but unfortunately, the person who did the work wasn't paying attention, and by copy-pasting the code, created a bug that resulted in `flame1` being assigned to both types of effects while `flame5` remained unused.
  
  Fortunately for us, this issue is easy to spot, and we can restore everything as originally planned!
  
  <p align="left">
    <img width="800" height="600" alt="flame5" src="https://github.com/user-attachments/assets/37cfca2d-67c0-400a-88c0-3727d98e6efa" />
  </p>
  
  However, because this bug has been present in the game for a long time during its development, we can't guarantee that this effect was meant to be used in this form, since it was never tested or tweaked to this texture, but that doesn't mean it looks bad or that we shouldn't use it!
    
* ### [III][PS2] Water splashes from wheels during the rain
  The story behind this feature is quite interesting.
  
  When it rains, water is supposed to splash up from under a car's wheels. But as we know, nothing like that happens in any version of the game.

  The reason is that at some point during development, someone modified the effect and set a new, broken particle ID, which is almost transparent and nearly impossible to see.
  Fortunately, the previous version of this particle ID remained in the game, so we can simply restore everything to the way it was.
  
  Later, for the PC port, developers tried to fix and optimize this effect, but ended up breaking it even more.

  The plugin restores the code to its PS2 state and sets the old ID, thereby fixing it!

  <p align="left">
    <img width="800" height="600" alt="carwatersp" src="https://github.com/user-attachments/assets/3d522935-ad3c-4c8d-a2c1-ea14830146e5" />
  </p>

* ### [III] PS2 puddle physics
  On PS2, when a car drives through a puddle or a pond, the water adds extra resistance and slightly reduces its speed.
  
  This feature doesn't work on PC because the code for this feature was accidentally deleted since it was located next to the code for the puddle splash effect.
  
  The plugin restores the original PS2 code and lets you see this little detail in the game again!
  
  <p align="left">
    <img width="800" height="449" alt="puddle" src="https://github.com/user-attachments/assets/d0050254-eb88-474c-96d2-f5a95e59f830" />
  </p>

* ### [III/VC] Dark spots fix
  If you're familiar with the pre-release screenshots of GTA 3, then you probably know that earlier in the game, after an explosion or a molotov being thrown, scorched marks used to appear on the ground, and unfortunately, that feature didn't survive to the final release.
  
  <table>
    <th>
      alpha
      <img width="640" height="448" alt="gta3_068" src="https://github.com/user-attachments/assets/430d76ca-3821-4f48-ba2d-a20ba132320f" />
    </th>
    <th>
      late beta
      <img width="640" height="448" alt="grandtheftauto3_790screen017" src="https://github.com/user-attachments/assets/2035a2f4-9914-4c69-86f7-77b2c654695d" />
    </th>
  </table>
  
  But the good news is that the code for this feature is still fully intact in the game, and R* never even planned to remove it on purpose!
  
  It was accidentally broken during the late stages of development, someone was making some changes and accidentally swapped the last two arguments, and instead of ***30 000 ms*** lifetime and ***1*** scale for the effect, they set the scale to ***30 000*** and the lifetime to ***1 ms***.
  
  Once that's changed to how it should be, everything will work again!
  
  <p align="left">
    <img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/37c55740-5989-46e0-a290-1971614b06d1" />
  </p>

* ### [III] Restored PS2 and Vice City jet explosions
  When a car explodes, there's a chance that a jet will also form.
  This feature went through many changes during the game's development, ranging from a thin, long jet to giant spheres slightly smaller than the main explosion.
  
  <table>
    <th>
      alpha
      <img width="640" height="448" alt="gta3_02" src="https://github.com/user-attachments/assets/35cc8a5f-ee14-47d7-b421-ee8e226a0846" />
    </th>
    <th>
      beta
      <img width="640" height="448" alt="gta3_22" src="https://github.com/user-attachments/assets/f0504a0c-1430-4a0d-8d88-b815c297112b" />
    </th>
  </table>
  
  In its final iteration on PS2, it took the form of a small, barely visible trail, with a fairly low chance of appearing.
  
  On PC this ended up in a completely non-functional state, due to early Vice City code leaking into this version of the game, small bits of bike code were implemented, which, for some strange reason, changed the car component ID that was the source of the jet to a different one, completely preventing the effect from appearing.  
  
  The plugin restores PS2 behavior and, as a bonus, allows you to select a jet from Vice City which reminds one of its oldest known iterations.
  
  <table>
    <th>
      <img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/52006d76-14b1-40cf-923f-889843e7f569" />
    </th>
    <th>
      <img width="800" height="600" alt="image" src="https://github.com/user-attachments/assets/2f37ec0e-0e3c-4e08-9d20-5bf1b213e3dc" />
    </th>
  </table>

* ### [III] PS2 Rain
  In addition to particle effects downgrades, the PC version of the game also received a downgrade in rain density by reducing the number of rain streaks from ***50*** (as it was on PS2) to ***35***.
  
  <p align="left">
    <img width="800" height="600" alt="rain" src="https://github.com/user-attachments/assets/ef2eb29d-7269-48cf-830d-905d6371b189" />
  </p>
  
  And although these changes are barely noticeable, the plugin still gives you the option to restore the original look.

* ### [III] Additional PS2 2dfx changes
  In addition to the downgrades in pobj/2dfx code, the PC port also received changes to the resource files, which resulted in some of effects placed on the map looking slightly different. It's hard to say whether these changes were made intentionally to make things work better with the downgrades or they were accidental and came along with a different version of the map (it's a well known fact that the PC port has more objects).

  <p align="left">
    <img width="800" height="600" alt="pobj" src="https://github.com/user-attachments/assets/c1168bc5-edda-46f5-8fa7-0f667d313750" />
  </p>
  
  So, if you want these changes in your game, you have only two options:
  * Install [PS2 map](https://gtaforums.com/topic/829512-ps2-and-xbox-map-for-pc/) or [PS2 2dfx separately](http://rockstarvision.com/yolklov/Misc/mapsPS2_2dfx.7z) and start a new game (unfortunately, 2dfx are stored in a save file after starting a new game and the game never reads them from the resources again).
  * Or you can use the functionality provided by the plugin to modify 2dfx/pobj in your save file. Go to debugmenu(Ctrl + M) -> ParticleEx -> PObject -> Load PObjects and load `particleobjects_ps2.pobj`(_Make sure that you are not on a mission, also don't forget to save your game if you want to see these changes later_).

# Installation

* Download the archive from [Releases section](https://github.com/Fire-Head/ParticleEx/releases)
* Extract `ParticleEx.asi`, `ParticleEx.ini` and `ParticleEx` folder into your GTA 3/GTA Vice City root or `scripts/` directory
  * If you're using modloader, alternatively you can put everything into a subdirectory inside the `modloader/` and add these lines to your `modloader/modloader.ini`(make sure the paths are correct):
      ```ini
    [Profiles.Default.IgnoreFiles]
    ; Put wildcard to files to be ignored here (e.g. cheetah.dff, *.dff, path_in_mod/*.dff)
    ; XBOX2 is VC Only
    ParticleEx\ParticleEx\PS2\PARTICLE.CFG
    ParticleEx\ParticleEx\PS2\PARTICLE.TXD
    ParticleEx\ParticleEx\XBOX\particle.cfg
    ParticleEx\ParticleEx\XBOX\particle.txd
    ParticleEx\ParticleEx\XBOX2\particle.cfg
    ParticleEx\ParticleEx\XBOX2\particle.txd
      ```
> [!IMPORTANT]
> [UAL](https://github.com/ThirteenAG/Ultimate-ASI-Loader) is required to run the mod!

> [!NOTE]
> [debugmenu.dll](https://github.com/aap/debugmenu) is recommended to be installed!

# Supported game versions
* gta3.exe v1.0.
* gta3.exe v1.1.
* gta3.exe v1.1 Steam.
* gta-vc.exe v1.0.
* gta-vc.exe v1.1.
* gta-vc.exe Steam.
