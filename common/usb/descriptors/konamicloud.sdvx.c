#include "usb/descriptors/konamicloud.sdvx.h"

const USB_REPORT USB_ATTRIBUTES KonamiCloud_Report[] = {
  0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
  0x09, 0x04,        // Usage (Joystick)
  0xA1, 0x01,        // Collection (Application)
  0x09, 0x01,        //   Usage (Pointer)
  0xA1, 0x00,        //   Collection (Physical)
  0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
  0x09, 0x30,        //     Usage (X)
  0x09, 0x31,        //     Usage (Y)
  // NOTE: This technically should be 0x80 to cover the full range.
  0x15, 0x81,        //     Logical Minimum (-127)
  0x25, 0x7F,        //     Logical Maximum (127)
  0x75, 0x08,        //     Report Size (8)
  0x95, 0x02,        //     Report Count (2)
  0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x05, 0x09,        //     Usage Page (Button)
  0x19, 0x01,        //     Usage Minimum (0x01)
  0x29, 0x10,        //     Usage Maximum (0x10)
  0x15, 0x00,        //     Logical Minimum (0)
  0x25, 0x01,        //     Logical Maximum (1)
  0x75, 0x01,        //     Report Size (1)
  0x95, 0x10,        //     Report Count (16)
  0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x75, 0x08,        //     Report Size (8)
  0x95, 0x01,        //     Report Count (1)
  0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0xC0,              //   End Collection
  // NOTE: This device does not normally provide an output report.
#include "usb/descriptors/output.c"
  0xC0,              // End Collection
};

// When differing, original values are commented to the right
const USB_DEVICE USB_ATTRIBUTES KonamiCloud_Device = {
  .bLength          = sizeof(USB_DEVICE),                     // 18
  .bDescriptorType  = USB_DEVICE_TYPE,                        // 0x01
  .bcdUSB           = 0x0110,                                 // 0x0200
  .bDeviceClass     = 0,
  .bDeviceSubClass  = 0,
  .bDeviceProtocol  = 0,
  .bMaxPacketSize0  = USB_DEVICE_MAX_PACKET_SIZE,             // 8
  .idVendor         = 0x1ccf,
  .idProduct        = 0x101c,
  .bcdDevice        = 0x0410,
  .iManufacturer    = StringID_Vendor_KonamiCloud,            // 1
  .iProduct         = StringID_Product_KonamiCloud,           // 2
  .iSerialNumber    = StringID_None,                          // 3
  .bNumConfigurations = 1
};

const USB_CONFIG USB_ATTRIBUTES KonamiCloud_Configuration = {
  .Config = {
    .bLength                = sizeof(USB_CONFIG_HEADER),      // 9
    .bDescriptorType        = USB_CONFIG_HEADER_TYPE,         // 0x02
    .wTotalLength           = sizeof(USB_CONFIG),             // 34
    .bNumInterfaces         = InterfaceID_Total,              // 1
    .bConfigurationValue    = 1,
    .iConfiguration         = StringID_None,                  // 0
    .bmAttributes           = USB_CONFIG_HEADER_ATTRS,        // 0x80, Not Self-Powered, No Remote-Wake
    .bMaxPower              = USB_CONFIG_HEADER_MAX_POWER,    // 100 (200mA)
  },

  .HID_Interface = {
    .bLength                = sizeof(USB_INTERFACE),          // 9
    .bDescriptorType        = USB_INTERFACE_TYPE,             // 0x04
    .bInterfaceNumber       = InterfaceID_Joystick,           // 0
    .bAlternateSetting      = 0,
    .bNumEndpoints          = 2,                              // 1
    .bInterfaceClass        = USB_INTERFACE_CLASS,            // 0x03
    .bInterfaceSubClass     = 0,
    .bInterfaceProtocol     = 0,
    .iInterface             = StringID_None,                  // 1
  },

  .HID_Report = {
    .bLength                = sizeof(USB_HID_DESCRIPTOR),     // 9
    .bDescriptorType        = USB_HID_DESCRIPTOR_TYPE,        // 0x21
    .bcdHID                 = 0x0111,
    .bCountryCode           = 0x21,
    .bNumDescriptors        = 1,
    .bDescriptorType2       = USB_HID_DESCRIPTOR_REPORT_TYPE, // 0x22
    .wDescriptorLength      = sizeof(KonamiCloud_Report)      // 50
  },

  .HID_ReportINEndpoint = {
    .bLength                = sizeof(USB_ENDPOINT),           // 7
    .bDescriptorType        = USB_ENDPOINT_TYPE,              // 0x05
    .bEndpointAddress       = USB_ENDPOINT_ADDR_IN,           // 0x81
    .bmAttributes           = USB_ENDPOINT_ATTRS_IN,          // 0x03, Interrupt
    .wMaxPacketSize         = USB_ENDPOINT_SIZE,              // 16
    .bInterval              = 0x01                            // 4
  },
  // NOTE: This device does not normally provide an output endpoint.
  .HID_ReportOUTEndpoint = {
    .bLength                = sizeof(USB_ENDPOINT),
    .bDescriptorType        = USB_ENDPOINT_TYPE,

    .bEndpointAddress       = USB_ENDPOINT_ADDR_OUT,
    .bmAttributes           = USB_ENDPOINT_ATTRS_OUT,

    .wMaxPacketSize         = USB_ENDPOINT_SIZE,
    .bInterval              = 0x01
  },
};

//  Default behavior:
//  * Buttons: A, B, C, D, L, R, two gaps, Start
//  * Analogs:  VOL-L (X), VOL-R (Y) (if available, note 0-255 scales to -128-127)
//  * Encoders: VOL-L (X), VOL-R (Y) (if not available)
WEAK void CALLBACK_OnKonamiCloudInputRequest(USB_InputReport_KonamiCloud_t *input) {
  const uint16_t buttons = Button_GetAll();
  input->buttons  =  buttons & 0x003F;
  input->buttons |= (buttons & 0x0040) << 2;

#if (ANALOG_CHANNELS_ACTIVE >= 2)
  input->vol_l = Analog_Get(0) ^ 0x80;
  input->vol_r = Analog_Get(1) ^ 0x80;
#else
  input->vol_l = Encoder_LogicalPercent(0);
  input->vol_r = Encoder_LogicalPercent(1);
#endif
}
