# Niran MonoDelay

A JUCE 7.0.12 audio plugin (VST3, Windows) that recreates the layout and
control set of a classic dark-panel mono delay, finished in a white/dirty-white
chassis, with the cube-grid "step" section replaced by a **velocity pipe
editor** — an FL-Studio-piano-roll-style lane where each vertical pipe sets
the feedback level of one delay repeat within a 1-bar cycle.

## Controls

- **DELAY** — sync division (1/1 … 1/64, plus dotted & triplet values) or a
  free millisecond value when **SYNC** is off.
- **FEEDBACK** / **MIX** — overall feedback and dry/wet amount.
- **Pipe editor** — click/drag any pipe to set its repeat's velocity (0–127).
  The number of pipes always matches the current sync division (or, when
  unsynced, however many repeats fit in one bar at the host tempo). A VU-style
  meter on the right animates in real time to show the level of whichever
  repeat is currently playing.
- **LO FILTER / HI FILTER** — high-pass / low-pass shaping of the feedback path.
- **PING PONG** — alternates repeats hard left/right.
- **WIDTH** — stereo width of the wet signal.

Tempo is taken from the host transport (falls back to 120 BPM if the host
doesn't report one), so there's no separate BPM control in the UI.

## Building

This project is built with **CMake** and fetches **JUCE 7.0.12** automatically
via `FetchContent` — no manual JUCE install is required.

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

The VST3 will be produced under:
```
build/HadenianMonoDelay_artefacts/Release/VST3/Hadenian MonoDelay.vst3
```

### GitHub Actions

`.github/workflows/build.yml` builds the plugin on `windows-latest` and
uploads the `.vst3` as a workflow artifact on every push, pull request, and
manual `workflow_dispatch` run.

## Project layout

```
CMakeLists.txt
Source/
  Parameters.h          Parameter IDs, sync-division table, layout creation
  DelayEngine.h/.cpp     Multi-tap "velocity pipe" delay DSP
  PluginProcessor.h/.cpp AudioProcessor: parameters, state save/load, audio callback
  PluginEditor.h/.cpp     Main editor layout (knobs, buttons, title bar)
  PipeEditor.h/.cpp       The velocity pipe editor + VU meter component
  CustomLookAndFeel.h/.cpp White/dirty-white knob & button drawing
```
