# HEARTHWAKE: Game Design Document (v0.1)

## 1. Overview
- **Genre:** co-op survival crafting (1–4 players)
- **Engine:** Unreal Engine 5.8, gameplay and networking in C++
- **Platform:** PC (Windows); listen server, dedicated server later
- **Inspirations:** Valheim (structural building, biome progression), Don't Starve Together (co-op survival pressure)

## 2. Design pillars
1. **Warmth is territory.** Hearths create safe zones; expanding the network is progress.
2. **Together is better.** Tasks split naturally between gathering, building and defending.
3. **The night is a test.** Each night checks whether your base was built well.

## 3. Core loop
Day: gather → craft tools → build and fuel hearths. Night: defend against frost-wraiths. Dawn: repair, expand into a colder biome.

## 4. Systems
| System | Design |
|---|---|
| Warmth | Decays away from active hearths; low warmth slows you and drains health |
| Hunger / Stamina | Food buffs stamina regeneration; sprinting and tools cost stamina |
| Gathering | Trees, rocks and frost-crystals, each with a tool-tier requirement; they respawn over time |
| Crafting | Recipes gated by crafting stations (Workbench → Forge → Rune Table); queued crafting with progress |
| Building | Wood → stone → rune stone; support pieces carry weight; removing a support can collapse what depends on it |
| Enemies | Frost-wraiths target hearths first, then players; the spawn director scales with player count |

## 5. World
One island with three biomes (Pine Coast, Frozen Moor, Glacier Peak), scattered by a seeded PCG graph. The day/night cycle lasts 20 minutes in total.

## 6. Networking model
The server owns all game state. Clients send intent (for example "move item from slot A to slot B"), and the server validates it and replicates the result. Every inventory request has an ID so a repeated packet cannot duplicate items. Placed structures go dormant to save bandwidth.

## 7. Scope of the MVP
1 island, 3 biomes, 30 items, 20 recipes, 15 building pieces, 2 enemy types, and a world save. **Out of scope:** boats, bosses, and dedicated-server hosting services.

## 8. Success criteria
- No item duplication or loss under 150 ms lag and 2% packet loss
- The same seed produces the same resource layout
- 4 players at 60 fps on the host (RTX 4050 Laptop, medium settings)
