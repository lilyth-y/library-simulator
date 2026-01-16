# Library Simulator Asset Style Guide (Chibi Cartoon, 2.5D Side View)

## Goals
- Build a calm library with a light wizard-tower vibe.
- Use chibi proportions with rounded, friendly silhouettes.
- Maintain a 2.5D side-view presentation for readability.

## Art Direction
- Mood: warm candlelight, cozy, quiet, slightly magical.
- Palette: warm browns, muted greens/teals, soft gold highlights.
- Shapes: rounded edges, simplified forms, low detail density.
- Materials: matte/soft, minimal roughness variation, no harsh metallics.

## Chibi Proportion Guide
- Head: 45-55% of total character height.
- Torso: short and wide, about 25-30% height.
- Limbs: short, thicker than realistic, with simple joints.
- Eyes: large and expressive, minimal facial detail.
- Accessories: oversized but simple (book bag, apron, wand-like pointer).

## 2.5D Side-View Setup
- Camera: fixed side view, perspective with low FOV (20-35).
- Movement: constrain to X/Z plane, lock Y where possible.
- Depth: layer foreground/midground/background props for parallax.
- Scale: keep books, shelves, and character sizes consistent for clarity.

## Asset Scope (MVP)
Characters:
- Librarian (chibi) with basic locomotion and interact poses.
- Patron (chibi) with idle and simple "rude" gesture.

Props:
- Books: 3-5 variations (size, color, spine label).
- Shelves: 2-3 variations with category label space.
- Table, cart, PC terminal, candle, lantern.
- Wizard accents: arc window, spiral stair segment, rune decal.

Audio:
- Book drop/impact, page rustle, soft room ambience, "shush" effect.

## Free Asset Sources (Common Options)
- Unreal Marketplace (Free).
- Kenney (CC0).
- Poly Pizza (CC0).
- Quaternius (Free).
- Sketchfab (CC0 filter).
- Mixamo (free rigged animations).

## Search Keywords
Environment:
- "low poly library", "stylized library interior", "cozy library"
- "wizard tower interior", "arc window", "spiral staircase"
- "stylized bookshelf", "book props", "wooden desk", "candle"

Characters:
- "chibi character", "cute stylized character", "cartoon librarian"
- "low poly villager", "fantasy scholar"

Animations:
- "mixamo idle", "mixamo walk", "mixamo carry", "mixamo interact"

## Import and Integration Checklist
- Confirm license (prefer CC0; record attribution if required).
- Match scale to UE units (1m = 100 units).
- Normalize pivots for shelves/books (bottom-center).
- Create simple collision for books and shelves.
- Assign a consistent material set (warm wood, muted fabric).

## Blueprint Hook Targets
- Mission UI: bind to Task Manager events.
- Shelf placement: play feedback FX/SFX on correct/incorrect placement.
- PC display: show search results in UI.
- Patron shush: trigger reaction animation/sound.

## Acceptance Criteria
- Character silhouettes read clearly at side view.
- Warm, cozy tone visible without post-processing heavy effects.
- Books feel physical and readable when stacked.
- Wizard accents are subtle and do not overpower the library mood.
