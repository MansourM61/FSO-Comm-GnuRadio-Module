#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: FSO Communication Block Modules Test
# Author: M Mansour Abadi
# Description: Modules from FSO_Comm are used in a simple FSO comunication link including various channel effects.
# Generated: Tue Oct 29 17:50:38 2019
##################################################

from distutils.version import StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from PyQt5 import Qt
from PyQt5 import Qt, QtCore
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import qtgui
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import FSO_Comm
import numpy
import sip
import sys
from gnuradio import qtgui


class FSO_Comm_Demo(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "FSO Communication Block Modules Test")
        Qt.QWidget.__init__(self)
        self.setWindowTitle("FSO Communication Block Modules Test")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "FSO_Comm_Demo")

        if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
            self.restoreGeometry(self.settings.value("geometry").toByteArray())
        else:
            self.restoreGeometry(self.settings.value("geometry", type=QtCore.QByteArray))

        ##################################################
        # Variables
        ##################################################
        self.wavelength = wavelength = 850e-9
        self.vis = vis = 1000
        self.samp_rate = samp_rate = 32000
        self.link_len = link_len = 100
        self.jitter = jitter = 0.05
        self.Z_0 = Z_0 = 50
        self.Tx_Dia = Tx_Dia = 3e-3
        self.Theta_0 = Theta_0 = 0.05
        self.T_0 = T_0 = 50e-3
        self.Sample_Offset = Sample_Offset = 0
        self.Rx_Dia = Rx_Dia = 50e-3
        self.Resp = Resp = 0.7
        self.P_n = P_n = 1e-6
        self.P_0 = P_0 = 1e-3
        self.Gain = Gain = 1e3
        self.Ext_Ratio = Ext_Ratio = 10
        self.Cn2 = Cn2 = 5e-12
        self.Chunck_Size = Chunck_Size = 200
        self.BW = BW = 2.5e3

        ##################################################
        # Blocks
        ##################################################
        self.qtgui_time_sink_x_0 = qtgui.time_sink_f(
        	1024*20, #size
        	samp_rate, #samp_rate
        	"", #name
        	1 #number of inputs
        )
        self.qtgui_time_sink_x_0.set_update_time(0.10)
        self.qtgui_time_sink_x_0.set_y_axis(-0.1e-3, 2.5e-3)

        self.qtgui_time_sink_x_0.set_y_label('Amplitude', "")

        self.qtgui_time_sink_x_0.enable_tags(-1, True)
        self.qtgui_time_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, 0, "")
        self.qtgui_time_sink_x_0.enable_autoscale(False)
        self.qtgui_time_sink_x_0.enable_grid(False)
        self.qtgui_time_sink_x_0.enable_axis_labels(True)
        self.qtgui_time_sink_x_0.enable_control_panel(False)
        self.qtgui_time_sink_x_0.enable_stem_plot(False)

        if not True:
          self.qtgui_time_sink_x_0.disable_legend()

        labels = ['', '', '', '', '',
                  '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
                  "magenta", "yellow", "dark red", "dark green", "blue"]
        styles = [1, 1, 1, 1, 1,
                  1, 1, 1, 1, 1]
        markers = [-1, -1, -1, -1, -1,
                   -1, -1, -1, -1, -1]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
                  1.0, 1.0, 1.0, 1.0, 1.0]

        for i in xrange(1):
            if len(labels[i]) == 0:
                self.qtgui_time_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_time_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_time_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_time_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_time_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_time_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_time_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_time_sink_x_0_win)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_char*1, samp_rate,True)
        self.blocks_repeat_0 = blocks.repeat(gr.sizeof_float*1, 4)
        self.blocks_char_to_float_0 = blocks.char_to_float(1, 1)
        self.analog_random_source_x_0 = blocks.vector_source_b(map(int, numpy.random.randint(0, 2, 1000)), True)
        self.FSO_Comm_Turbulence_ff_0 = FSO_Comm.Turbulence_ff(Cn2, wavelength, link_len, Rx_Dia, T_0, samp_rate)
        self.FSO_Comm_Pointing_Errors_ff_0 = FSO_Comm.Pointing_Errors_ff(jitter, link_len, Tx_Dia, Theta_0, Rx_Dia, T_0, samp_rate)
        self.FSO_Comm_Optical_Receiver_ff_0 = FSO_Comm.Optical_Receiver_ff(Resp, Gain, Z_0, P_n)
        self.FSO_Comm_Laser_ff_0 = FSO_Comm.Laser_ff(P_0, wavelength, Ext_Ratio)
        self.FSO_Comm_Geometric_Loss_ff_0 = FSO_Comm.Geometric_Loss_ff(Tx_Dia, Theta_0, link_len, Rx_Dia)
        self.FSO_Comm_FogSmoke_Loss_ff_0 = FSO_Comm.FogSmoke_Loss_ff(wavelength, link_len, vis)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.FSO_Comm_FogSmoke_Loss_ff_0, 0), (self.FSO_Comm_Optical_Receiver_ff_0, 0))
        self.connect((self.FSO_Comm_Geometric_Loss_ff_0, 0), (self.FSO_Comm_Turbulence_ff_0, 0))
        self.connect((self.FSO_Comm_Laser_ff_0, 0), (self.FSO_Comm_Geometric_Loss_ff_0, 0))
        self.connect((self.FSO_Comm_Optical_Receiver_ff_0, 0), (self.qtgui_time_sink_x_0, 0))
        self.connect((self.FSO_Comm_Pointing_Errors_ff_0, 0), (self.FSO_Comm_FogSmoke_Loss_ff_0, 0))
        self.connect((self.FSO_Comm_Turbulence_ff_0, 0), (self.FSO_Comm_Pointing_Errors_ff_0, 0))
        self.connect((self.analog_random_source_x_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.blocks_char_to_float_0, 0), (self.blocks_repeat_0, 0))
        self.connect((self.blocks_repeat_0, 0), (self.FSO_Comm_Laser_ff_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_char_to_float_0, 0))

    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "FSO_Comm_Demo")
        self.settings.setValue("geometry", self.saveGeometry())
        event.accept()

    def get_wavelength(self):
        return self.wavelength

    def set_wavelength(self, wavelength):
        self.wavelength = wavelength
        self.FSO_Comm_Turbulence_ff_0.set_Wavelen(self.wavelength)
        self.FSO_Comm_Laser_ff_0.set_Wavelen(self.wavelength)
        self.FSO_Comm_FogSmoke_Loss_ff_0.set_Wavelen(self.wavelength)

    def get_vis(self):
        return self.vis

    def set_vis(self, vis):
        self.vis = vis
        self.FSO_Comm_FogSmoke_Loss_ff_0.set_Vis(self.vis)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.qtgui_time_sink_x_0.set_samp_rate(self.samp_rate)
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)
        self.FSO_Comm_Turbulence_ff_0.set_SampRate(self.samp_rate)
        self.FSO_Comm_Pointing_Errors_ff_0.set_SampRate(self.samp_rate)

    def get_link_len(self):
        return self.link_len

    def set_link_len(self, link_len):
        self.link_len = link_len
        self.FSO_Comm_Turbulence_ff_0.set_LinkLen(self.link_len)
        self.FSO_Comm_Pointing_Errors_ff_0.set_LinkLen(self.link_len)
        self.FSO_Comm_Geometric_Loss_ff_0.set_LinkLen(self.link_len)
        self.FSO_Comm_FogSmoke_Loss_ff_0.set_LinkLen(self.link_len)

    def get_jitter(self):
        return self.jitter

    def set_jitter(self, jitter):
        self.jitter = jitter
        self.FSO_Comm_Pointing_Errors_ff_0.set_Jitter(self.jitter)

    def get_Z_0(self):
        return self.Z_0

    def set_Z_0(self, Z_0):
        self.Z_0 = Z_0
        self.FSO_Comm_Optical_Receiver_ff_0.set_Imp(self.Z_0)

    def get_Tx_Dia(self):
        return self.Tx_Dia

    def set_Tx_Dia(self, Tx_Dia):
        self.Tx_Dia = Tx_Dia
        self.FSO_Comm_Pointing_Errors_ff_0.set_Tx_Dia(self.Tx_Dia)
        self.FSO_Comm_Geometric_Loss_ff_0.set_Tx_Dia(self.Tx_Dia)

    def get_Theta_0(self):
        return self.Theta_0

    def set_Theta_0(self, Theta_0):
        self.Theta_0 = Theta_0
        self.FSO_Comm_Pointing_Errors_ff_0.set_Tx_Theta(self.Theta_0)
        self.FSO_Comm_Geometric_Loss_ff_0.set_Tx_DivAng(self.Theta_0)

    def get_T_0(self):
        return self.T_0

    def set_T_0(self, T_0):
        self.T_0 = T_0
        self.FSO_Comm_Turbulence_ff_0.set_TempCorr(self.T_0)
        self.FSO_Comm_Pointing_Errors_ff_0.set_TempCorr(self.T_0)

    def get_Sample_Offset(self):
        return self.Sample_Offset

    def set_Sample_Offset(self, Sample_Offset):
        self.Sample_Offset = Sample_Offset

    def get_Rx_Dia(self):
        return self.Rx_Dia

    def set_Rx_Dia(self, Rx_Dia):
        self.Rx_Dia = Rx_Dia
        self.FSO_Comm_Turbulence_ff_0.set_Rx_Dia(self.Rx_Dia)
        self.FSO_Comm_Pointing_Errors_ff_0.set_Rx_Dia(self.Rx_Dia)
        self.FSO_Comm_Geometric_Loss_ff_0.set_Rx_Dia(self.Rx_Dia)

    def get_Resp(self):
        return self.Resp

    def set_Resp(self, Resp):
        self.Resp = Resp
        self.FSO_Comm_Optical_Receiver_ff_0.set_Resp(self.Resp)

    def get_P_n(self):
        return self.P_n

    def set_P_n(self, P_n):
        self.P_n = P_n
        self.FSO_Comm_Optical_Receiver_ff_0.set_P_n(self.P_n)

    def get_P_0(self):
        return self.P_0

    def set_P_0(self, P_0):
        self.P_0 = P_0
        self.FSO_Comm_Laser_ff_0.set_P_avg(self.P_0)

    def get_Gain(self):
        return self.Gain

    def set_Gain(self, Gain):
        self.Gain = Gain
        self.FSO_Comm_Optical_Receiver_ff_0.set_G_TIA(self.Gain)

    def get_Ext_Ratio(self):
        return self.Ext_Ratio

    def set_Ext_Ratio(self, Ext_Ratio):
        self.Ext_Ratio = Ext_Ratio
        self.FSO_Comm_Laser_ff_0.set_ExtRatio(self.Ext_Ratio)

    def get_Cn2(self):
        return self.Cn2

    def set_Cn2(self, Cn2):
        self.Cn2 = Cn2

    def get_Chunck_Size(self):
        return self.Chunck_Size

    def set_Chunck_Size(self, Chunck_Size):
        self.Chunck_Size = Chunck_Size

    def get_BW(self):
        return self.BW

    def set_BW(self, BW):
        self.BW = BW


def main(top_block_cls=FSO_Comm_Demo, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()
    tb.start()
    tb.show()

    def quitting():
        tb.stop()
        tb.wait()
    qapp.aboutToQuit.connect(quitting)
    qapp.exec_()


if __name__ == '__main__':
    main()
