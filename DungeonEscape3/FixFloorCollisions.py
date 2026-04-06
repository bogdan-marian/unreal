import unreal

def fix_floor_collisions():
    asset_registry = unreal.AssetRegistryHelpers.get_asset_registry()
    
    # Path to the Medieval Dungeon architecture meshes
    mesh_paths = [
        "/Game/MedievalDungeon/Meshes/Architecture",
    ]
    
    updated_count = 0
    
    for path in mesh_paths:
        # Get all assets in the path
        assets = asset_registry.get_assets_by_path(path, recursive=True)
        
        for asset_data in assets:
            if asset_data.asset_class_path.asset_name == "StaticMesh":
                mesh = asset_data.get_asset()
                
                body_setup = mesh.get_editor_property("body_setup")
                if body_setup:
                    # Change collision to Use Complex Collision As Simple
                    # This fixes the issue of falling through the floor or walking through walls
                    body_setup.set_editor_property("collision_trace_flag", unreal.CollisionTraceFlag.CTF_USE_COMPLEX_AS_SIMPLE)
                    
                    # Ensure the change is registered
                    mesh.set_editor_property("body_setup", body_setup)
                    
                    # Save the asset
                    unreal.EditorAssetLibrary.save_loaded_asset(mesh)
                    print(f"Fixed collision for: {mesh.get_name()}")
                    updated_count += 1

    print(f"Finished! Successfully fixed collision for {updated_count} meshes in the Architecture folder.")

if __name__ == "__main__":
    fix_floor_collisions()
