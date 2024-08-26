# Scope of this project
Add additional functionality to [omriharels original project](https://github.com/omriharel/deej) like
- assigning individual processes or groups of processes to either the default sound device or an alternative one specified in config.yaml using switches
- add mute functionality
- add status updates via LEDs

## Probable ways of implementing new functionality
- extending serial messages by markers like S for switches and V for volume

possible serial output of Arduino:
  ```
  V0|V14|V192|V5|S1|S0|S2|S1
  ```
- handling muting individual channels Arduino side (middle position of SPDT switches)
- LEDs will be used to display muted state (on) or operational state (off). Blinking to indicate alternative output might be added later.

Files for custom PCB design and 3D printed case will be provided later.
