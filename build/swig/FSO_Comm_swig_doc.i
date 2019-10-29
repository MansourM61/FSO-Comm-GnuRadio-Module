
/*
 * This file was automatically generated using swig_doc.py.
 *
 * Any changes to it will be lost next time it is regenerated.
 */




%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff "FSO Channel Analyser.

Use this block alongside an on-off keying (OOK) pulse sequence as the source to estimate Q-factor, and scintillation indices for levels '0' and '1' of FSO channel. It is also possible to use a constant optical intensity and measure scintillation index for average level.

Constructor Specific Documentation:

Make a Channel Analyser block.

Args:
    mode : mode of estimation, true = use a constant optical intensity as the source, false = use a random OOK pulse sequence
    ChunkSize : required number of pulses in each iteration to calculate the outputs (number of pulses)
    SamplingOffset : offset index of sampling point from the centre of OOK pulse (+/- offset)
    BandWidth : bandwidth of generated OOK pulse (Hz)
    SampRate : sample rate of the signal (samples per second)"

%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff::set_mode "Set channel analyser mode."

%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff::mode "Return current channel analyser mode."

%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff::set_ChunkSize "Set channel analyser chunk size."

%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff::ChunkSize "Return current channel analyser chunk size."

%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff::set_SamplingOffset "Set channel analyser sampling offset."

%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff::SamplingOffset "Return current channel analyser sampling offset."

%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff::set_BandWidth "Set channel analyser bandwidth."

%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff::BandWidth "Return current channel analyser bandwidth."

%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff::set_SampRate "Set channel analyser sampling rate."

%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff::SampRate "Return current channel analyser sampling rate."

%feature("docstring") gr::FSO_Comm::Channel_Analyser_ff::make "FSO Channel Analyser.

Use this block alongside an on-off keying (OOK) pulse sequence as the source to estimate Q-factor, and scintillation indices for levels '0' and '1' of FSO channel. It is also possible to use a constant optical intensity and measure scintillation index for average level.

Constructor Specific Documentation:

Make a Channel Analyser block.

Args:
    mode : mode of estimation, true = use a constant optical intensity as the source, false = use a random OOK pulse sequence
    ChunkSize : required number of pulses in each iteration to calculate the outputs (number of pulses)
    SamplingOffset : offset index of sampling point from the centre of OOK pulse (+/- offset)
    BandWidth : bandwidth of generated OOK pulse (Hz)
    SampRate : sample rate of the signal (samples per second)"

%feature("docstring") gr::FSO_Comm::FogSmoke_Loss_ff "Fog/Smoke Loss in FSO Channel.

The block uses Kim model to simulate the attenuation of fog/smoke in FSO channels based on visibility.

Constructor Specific Documentation:

Make a FogSmoke Loss block.

Args:
    Wavelen : optical beam wavelength (m)
    LinkLen : FSO channel link length (m)
    Vis : FSO channel visibility (m)"

%feature("docstring") gr::FSO_Comm::FogSmoke_Loss_ff::set_Wavelen "Set fog/smoke loss wavelength."

%feature("docstring") gr::FSO_Comm::FogSmoke_Loss_ff::Wavelen "Return current fogsmoke loss wavelength."

%feature("docstring") gr::FSO_Comm::FogSmoke_Loss_ff::set_LinkLen "Set fog/smoke loss link length."

%feature("docstring") gr::FSO_Comm::FogSmoke_Loss_ff::LinkLen "Return current fog/smoke loss link length."

%feature("docstring") gr::FSO_Comm::FogSmoke_Loss_ff::set_Vis "Set fog/smoke loss visibility."

%feature("docstring") gr::FSO_Comm::FogSmoke_Loss_ff::Vis "Return current fog/smoke loss visibility."

%feature("docstring") gr::FSO_Comm::FogSmoke_Loss_ff::make "Fog/Smoke Loss in FSO Channel.

The block uses Kim model to simulate the attenuation of fog/smoke in FSO channels based on visibility.

Constructor Specific Documentation:

Make a FogSmoke Loss block.

Args:
    Wavelen : optical beam wavelength (m)
    LinkLen : FSO channel link length (m)
    Vis : FSO channel visibility (m)"

%feature("docstring") gr::FSO_Comm::Geometric_Loss_ff "Geometric Loss in FSO Channel.

Using geometric optics, the beam propagation loss is estimated for given beam properties.

Constructor Specific Documentation:

Make a geometric loss block.

Args:
    Tx_Dia : transmitter aperture diameter (m)
    Tx_DivAng : transmitter half-angle beam divergence (Deg)
    LinkLen : FSO channel link length (m)
    Rx_Dia : receiver aperture diameter (m)"

%feature("docstring") gr::FSO_Comm::Geometric_Loss_ff::set_Tx_Dia "Set geometric loss transmitter aperture diameter."

%feature("docstring") gr::FSO_Comm::Geometric_Loss_ff::Tx_Dia "Return current geometric loss transmitter aperture diameter."

%feature("docstring") gr::FSO_Comm::Geometric_Loss_ff::set_Tx_DivAng "Set geometric loss transmitter full-angle divergence angle."

%feature("docstring") gr::FSO_Comm::Geometric_Loss_ff::Tx_DivAng "Return current geometric loss transmitter full-angle divergence angle."

%feature("docstring") gr::FSO_Comm::Geometric_Loss_ff::set_LinkLen "Set geometric loss transmitter link length."

%feature("docstring") gr::FSO_Comm::Geometric_Loss_ff::LinkLen "Return current geometric loss transmitter link length."

%feature("docstring") gr::FSO_Comm::Geometric_Loss_ff::set_Rx_Dia "Set geometric loss receiver aperture diameter."

%feature("docstring") gr::FSO_Comm::Geometric_Loss_ff::Rx_Dia "Return cyurrent geometric loss receiver aperture diameter."

%feature("docstring") gr::FSO_Comm::Geometric_Loss_ff::make "Geometric Loss in FSO Channel.

Using geometric optics, the beam propagation loss is estimated for given beam properties.

Constructor Specific Documentation:

Make a geometric loss block.

Args:
    Tx_Dia : transmitter aperture diameter (m)
    Tx_DivAng : transmitter half-angle beam divergence (Deg)
    LinkLen : FSO channel link length (m)
    Rx_Dia : receiver aperture diameter (m)"

%feature("docstring") gr::FSO_Comm::Laser_ff "FSO Laser Module.

The block generate optical power output based on average power and extinction ratio.

Constructor Specific Documentation:

Make a laser module block.

Args:
    P_avg : average optical power (W)
    Wavelen : optical beam wavelength (m)
    ExtRatio : extiction ratio"

%feature("docstring") gr::FSO_Comm::Laser_ff::set_P_avg "Set laser module average optical power."

%feature("docstring") gr::FSO_Comm::Laser_ff::P_avg "Return current laser module average optical power."

%feature("docstring") gr::FSO_Comm::Laser_ff::set_Wavelen "Set laser module wavelength."

%feature("docstring") gr::FSO_Comm::Laser_ff::Wavelen "Return current laser module wavelength."

%feature("docstring") gr::FSO_Comm::Laser_ff::set_ExtRatio "Set current laser module extinction ratio."

%feature("docstring") gr::FSO_Comm::Laser_ff::ExtRatio "Return current laser module extinction ratio."

%feature("docstring") gr::FSO_Comm::Laser_ff::make "FSO Laser Module.

The block generate optical power output based on average power and extinction ratio.

Constructor Specific Documentation:

Make a laser module block.

Args:
    P_avg : average optical power (W)
    Wavelen : optical beam wavelength (m)
    ExtRatio : extiction ratio"

%feature("docstring") gr::FSO_Comm::Optical_Receiver_ff "FSO Optical Receiver.

The optical receiver models a photodiode followed by a transimpedance amplifer (TIA) converting optical power to electrial current.

Constructor Specific Documentation:

Make an optical receiver block.

Args:
    Resp : photodiode responsivity (A/W)
    G_TIA : transimpedance amplifer (TIA) gain (Ohms)
    Imp : circuit impedance (Ohms)
    P_n : noise power (w)"

%feature("docstring") gr::FSO_Comm::Optical_Receiver_ff::set_Resp "Set optical receiver sensitivity."

%feature("docstring") gr::FSO_Comm::Optical_Receiver_ff::Resp "Return current optical receiver sensitivity."

%feature("docstring") gr::FSO_Comm::Optical_Receiver_ff::set_G_TIA "Set optical receiver TIA gain."

%feature("docstring") gr::FSO_Comm::Optical_Receiver_ff::G_TIA "Return current optical receiver TIA gain."

%feature("docstring") gr::FSO_Comm::Optical_Receiver_ff::set_Imp "Set optical receiver impedance."

%feature("docstring") gr::FSO_Comm::Optical_Receiver_ff::Imp "Return current optical receiver impedance."

%feature("docstring") gr::FSO_Comm::Optical_Receiver_ff::set_P_n "Set optical receiver noise power."

%feature("docstring") gr::FSO_Comm::Optical_Receiver_ff::P_n "Return current optical receiver noise power."

%feature("docstring") gr::FSO_Comm::Optical_Receiver_ff::make "FSO Optical Receiver.

The optical receiver models a photodiode followed by a transimpedance amplifer (TIA) converting optical power to electrial current.

Constructor Specific Documentation:

Make an optical receiver block.

Args:
    Resp : photodiode responsivity (A/W)
    G_TIA : transimpedance amplifer (TIA) gain (Ohms)
    Imp : circuit impedance (Ohms)
    P_n : noise power (w)"

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff "FSO Pointing Errors Channel.

This block simulates the effect of pointing errors (vibration) in FSO channel.

Constructor Specific Documentation:

Make a pointing errors block.

Args:
    Jitter : vibration displacement (m)
    LinkLen : FSO channel link length (m)
    Tx_Dia : transmitter aperture diameter (m)
    Tx_Theta : transmitter beam half-angle divergence angle (Deg)
    Rx_Dia : receiver aperture diameter (m)
    TempCorr : temppral correlation of pointing errors channel (s)
    SampRate : sampling rate of signal (samples per second)"

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::set_Jitter "Set pointing errors jitter."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::Jitter "Return current pointing errors jitter."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::set_LinkLen "Set pointing errors link length."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::LinkLen "Return current pointing errors link length."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::set_Tx_Dia "Set pointing errors transmitter aperture diameter."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::Tx_Dia "Return current pointing errors transmitter aperture diameter."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::set_Tx_Theta "Set poinintg errors transmitter beam divergence."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::Tx_Theta "Return current poinintg errors transmitter beam divergence."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::set_Rx_Dia "Set pointing errors receiver aperture diameter."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::Rx_Dia "Return current pointing errors receiver aperture diameter."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::set_TempCorr "Set pointing errors temporal correlation."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::TempCorr "Return current pointing errors temporal correlation."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::set_SampRate "Set poinintg errors sampling rate."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::SampRate "Return current poinintg errors sampling rate."

%feature("docstring") gr::FSO_Comm::Pointing_Errors_ff::make "FSO Pointing Errors Channel.

This block simulates the effect of pointing errors (vibration) in FSO channel.

Constructor Specific Documentation:

Make a pointing errors block.

Args:
    Jitter : vibration displacement (m)
    LinkLen : FSO channel link length (m)
    Tx_Dia : transmitter aperture diameter (m)
    Tx_Theta : transmitter beam half-angle divergence angle (Deg)
    Rx_Dia : receiver aperture diameter (m)
    TempCorr : temppral correlation of pointing errors channel (s)
    SampRate : sampling rate of signal (samples per second)"

%feature("docstring") gr::FSO_Comm::Turbulence_ff "FSO Turbulence Channel.

This block simulates the effect of turbulence (scintillation) in FSO channel.

Constructor Specific Documentation:

Make a turbulence block.

Args:
    Cn2 : refractive index structure constant (m^(-2/3))
    Wavelen : optical beam wavelength (m)
    LinkLen : FSO channel link length (m)
    Rx_Dia : receiver aperture diameter (m)
    TempCorr : temppral correlation of turbulence channel (s)
    SampRate : sampling rate of signal (samples per second)"

%feature("docstring") gr::FSO_Comm::Turbulence_ff::set_Cn2 "Set turbulence Cn2."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::Cn2 "Return current turbulence Cn2."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::set_Wavelen "Set turbulence wavelength."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::Wavelen "Return current turbulence wavelength."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::set_LinkLen "Set turbulence link length."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::LinkLen "Return current turbulence link length."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::set_Rx_Dia "Set turbulence receiver apertture diameter."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::Rx_Dia "Return current turbulence receiver aperture diameter."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::set_TempCorr "Set turbulence temporal correlation."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::TempCorr "Return current turbulence temporal correlation."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::set_SampRate "Set turbulence sampling rate."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::SampRate "Return current turbulence sampling rate."

%feature("docstring") gr::FSO_Comm::Turbulence_ff::make "FSO Turbulence Channel.

This block simulates the effect of turbulence (scintillation) in FSO channel.

Constructor Specific Documentation:

Make a turbulence block.

Args:
    Cn2 : refractive index structure constant (m^(-2/3))
    Wavelen : optical beam wavelength (m)
    LinkLen : FSO channel link length (m)
    Rx_Dia : receiver aperture diameter (m)
    TempCorr : temppral correlation of turbulence channel (s)
    SampRate : sampling rate of signal (samples per second)"