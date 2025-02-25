# ESPHome Custom Component <a href="https://www.paypal.com/donate?hosted_button_id=6K9UYUZ4SZMVC"><img style="vertical-align:middle" src="https://www.paypalobjects.com/en_GB/i/btn/btn_donate_SM.gif"></a>

With the release of ESPHome 2025.2.0, custom components were removed from the ESPHome core.

This component brings back support for such components.

## DISCLAIMER

I lifted the custom component code from ESPHome 2024.10.0 as-is. It seems to work for me, but I only have a single project that has a custom component, so YMMV.

## USAGE

Add the following to your project's YAML:
```
external_components:
  - source:
      type: git
      url: https://github.com/robertklep/esphome-custom-component
    components: [ custom, custom_component ]
```

This should be enough to enable compilation of custom components again.

## LICENSE

The ESPHome license (mixed GPL3/MIT) applies. See [the LICENSE file](LICENSE) for more information.
