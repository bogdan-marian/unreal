#!/bin/bash

# Ensure Unreal Engine Python plugins are active and run the script
echo "Running UnrealEngine headless to fix floor collisions..."

"/Users/Shared/EpicGames/UE_5.7/Engine/Binaries/Mac/UnrealEditor-Cmd" \
  "/Users/bogdan/unreal-workspace/unreal/DungeonEscape3/DungeonEscape3.uproject" \
  -ExecutePythonScript="/Users/bogdan/unreal-workspace/unreal/DungeonEscape3/FixFloorCollisions.py" \
  -NoUI \
  -log

echo "Done! The collisions should now be fixed."
