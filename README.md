# Berlin2025_Sprint6

## Fixes

### Impossible to open the project

1. Removing the `DeadPlugin` directory.

2. Removing it from the content of `Plugins` in `Berlin2025_Sprint6.uproject`.

### Infinite actor spawning

1. Removing the `Event Tick` event in `GM_Level1`.

### Crystals not emitting sound

1. Fill the `set Crystal SFX` nodes with the appropriate SFXs in the `Event BeginPlay` event in `BP_Item_Crystals`.

2. Connect the two nodes in `SC_Anger`, `SC_Fear`, `SC_Hope`, `SC_Joy`, `SC_Remission` and `SC_Sadness`.

3. Set the value of `Volume` in `SC_Master` from `0.0` to `1.0`.

4. Set the value of `Fallof Distance` in `SA_Crystals` from `0.0` to `500.0`

### Crystals always having their white outline

1. Add a `Parent BeingPlay` node at the start of the `Event BeginPlay` event in `BP_Item_Crystals`.
