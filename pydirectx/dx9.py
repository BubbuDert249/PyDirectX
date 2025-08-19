import clr
from SharpDX import Direct3D9

def create_device():
    try:
        d3d = Direct3D9.Direct3D()
        adapter = 0  # primary GPU
        dev_type = Direct3D9.DeviceType.Hardware

        # Check if the device can run at least a simple level (HAL)
        caps = d3d.GetDeviceCaps(adapter, dev_type)
        if not (caps.DeviceCaps & Direct3D9.DeviceCaps.HWTransformAndLight):
            raise ValueError("DirectX 9 not supported on this GPU")

        present_params = Direct3D9.PresentParameters()
        present_params.Windowed = True
        present_params.SwapEffect = Direct3D9.SwapEffect.Discard
        present_params.BackBufferFormat = Direct3D9.Format.Unknown

        device = Direct3D9.Device(d3d, adapter, dev_type, None, Direct3D9.CreateFlags.HardwareVertexProcessing, present_params)
        return device

    except Exception as e:
        raise ValueError("DirectX 9 not supported on this GPU") from e
