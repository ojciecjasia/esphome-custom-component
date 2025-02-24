# ESPHome Custom Component

With the release of ESPHome 2025.2.0, custom components were removed from the ESPHome core.

This component brings back support for such components.

## DISCLAIMER

I lifted the custom component code from ESPHome 2024.10.0 as-is. It seems to work for me, but I only have a single project that has a custom component, so YMMV.

## Usage

Add the following to your project's YAML:
```
external_components:
  - source:
      type: git
      url: https://github.com/robertklep/esphome-custom-component
    components: [ custom ]
```

This should be enough to enable compilation of custom components again.
