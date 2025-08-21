import clr
import os
import sys
base_dir = os.path.dirname(os.path.abspath(__file__))
sharpdx_dir = os.path.join(base_dir, "sharpdx")
sys.path.append(sharpdx_dir)
clr.AddReference("SharpDX")
clr.AddReference("SharpDX.Direct3D11")
clr.AddReference("SharpDX.DXGI")
from SharpDX import Direct3D11, DXGI

def create_device():
    try:
        driver_types = [
            Direct3D11.DriverType.Hardware,
            Direct3D11.DriverType.Warp,
            Direct3D11.DriverType.Reference
        ]

        device = None
        context = None
        for driver in driver_types:
            try:
                device, context = Direct3D11.Device.CreateWithSwapChain(
                    driver,
                    Direct3D11.DeviceCreationFlags.None,
                    Direct3D11.FeatureLevel.Level_11_0,
                    DXGI.SwapChainDescription(
                        BufferCount=1,
                        ModeDescription=DXGI.ModeDescription(100, 100, DXGI.Rational(60,1), DXGI.Format.R8G8B8A8_UNorm),
                        IsWindowed=True,
                        OutputHandle=None,
                        SampleDescription=DXGI.SampleDescription(1,0),
                        SwapEffect=DXGI.SwapEffect.Discard,
                        Usage=DXGI.Usage.RenderTargetOutput
                    )
                )
                break
            except:
                continue

        if device is None:
            raise ValueError("DirectX 11 not supported on this GPU")

        return device

    except Exception as e:
        raise ValueError("DirectX 11 not supported on this GPU") from e
