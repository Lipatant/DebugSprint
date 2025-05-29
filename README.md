# Berlin2025_Sprint6

## Fixes

### Impossible to open the project

1. Removing the `DeadPlugin` directory.

2. Removing it from the content of `Plugins` in `Berlin2025_Sprint6.uproject`.

### Infinite actor spawning

1. Removing the `Event Tick` event in `GM_Level1`.

2. Removing the `Event Tick` event in `L_DeepCave`.

3. Removing the `CustomEvent` event in `WBP_HUD`.

### Crystals not emitting sound

1. Fill the `set Crystal SFX` nodes with the appropriate SFXs in the `Event BeginPlay` event in `BP_Item_Crystals`.

2. Connect the two nodes in `SC_Anger`, `SC_Fear`, `SC_Hope`, `SC_Joy`, `SC_Remission` and `SC_Sadness`.

3. Set the value of `Volume` in `SC_Master` from `0.0` to `1.0`.

4. Set the value of `Fallof Distance` in `SA_Crystals` from `0.0` to `500.0`

### Crystals always having their white outline

1. Add a `Parent BeingPlay` node at the start of the `Event BeginPlay` event in `BP_Item_Crystals`.

### Item interactions not being detected

1. Add `GM_Level1` to `L_DeepCave`.

2. Set the value of `Start with Tick Enabled` in `BP_FPSPlayer` from `false` to `true`.

3. Resetting the value of `Tags` in `BP_Item_Crystals` to the default array of size 1.

4. Connect the nodes `Start Look at Interactables` and `Display Info Text` at the end of the `Event Tick` event in `BP_FPSPlayer`.

5. Add a `Set Holding Object` node with an empty parameter at the end of the `ForceUngrab` event in `BP_FPSPlayer`.

6. Add a `Hide Info Text` function call from `HUDRef` at the end of the `LineTraceNotOverlapping` event in `BP_FPSPlayer`.

7. Remove the instances of the `Event Start Look at Interactables` and `Event Stop Look at Interactables` events in `BP_Item_Crystals`.

### Items always colliding with the player

1. Add a `HoldingObjectCollisionType` variable of type `ECollision Enabled Type` in `BP_FPS_Player`.

2. Insert `Set HoldingObjectCollisionType` from the previous `As BP Master Item`.`SM Shape`.`Get Collision Enabled` after the `Attach Actor to Actor` node in the `EnhancedInputActyion IA_PlayerInteract` event in `BP_FPS_Player`.

3. Insert `As BP Master Item`.`SM Shape`.`Set Collision Enabled` with `New Type` set to `Query and Probe` after the previous `Set HoldingObjectCollisionType` node.

4. Insert `Set Collision Enabled` from the previous `As BP Master Item`.`SM Shape`.`Get Collision Enabled` with `New Type` set to the `HoldingObjectCollisionType` variable after the `Detach from Actor` node in the `EnhancedInputActyion IA_PlayerInteract` event in `BP_FPS_Player`.

### Item grapping range being too long

1. Change the value of `LineTraceLength` from `750.0` to `500.0` in `BP_FPS_Player`.

### The game crashes instantly when running its exported version

1. Remove the `GameEngine=/Script/MissingPlugin.MagicEngineSubsystem` line in `Config/DefaultEngine.ini`.

### Crystal Pedestals being unusable after one use

1. Add an empty `Set CrystalOnPiedestral` at the end of the `On Component End Overlap (Sphere)` event in `BP_Item_CrystalPedestral`.
