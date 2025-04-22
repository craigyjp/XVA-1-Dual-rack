#include <Arduino.h>
#include "SectionFactory.h"
#include "SynthParameter.h"


Section SectionFactory::createDefaultSection() {
  return Section(labelDefault)
    .addParameter(SynthParameter(labelCutoff1).number(72))
    .addParameter(SynthParameter(labelResonance1).number(77))
    .addParameter(SynthParameter(labelCutoff2).number(78))
    .addParameter(SynthParameter(labelResonance2).number(79))
    .addParameter(
      SynthParameter(labelArpMode)
        .number(450)
        .max(5)
        .descriptions({ arpModesDescriptions[0],
                        arpModesDescriptions[1],
                        arpModesDescriptions[2],
                        arpModesDescriptions[3],
                        arpModesDescriptions[4],
                        arpModesDescriptions[5] }))
    .addParameter(SynthParameter(labelArpTempo).number(451))
    .addParameter(SynthParameter(labelMultiplier).number(453).min(1))
    .addParameter(SynthParameter(labelOctaves).number(454).max(10))
    .addParameter(
      SynthParameter(labelSequencer)
        .number(428)
        .max(1)
        .descriptions({ offOn[0],
                        offOn[1] }))
    .addParameter(SynthParameter(labelSequencerTempo).number(431))
    .addParameter(
      SynthParameter(labelGlide)
        .number(245)
        .max(2)
        .descriptions({ glideDescriptions[0],
                        glideDescriptions[1],
                        glideDescriptions[2] }))
    .addParameter(SynthParameter(labelGlideTime).number(246))
    .addParameter(
      SynthParameter(labelLegatoMode)
        .number(244)
        .max(1)
        .descriptions({ legatoDescriptions[0],
                        legatoDescriptions[1] }))
    .addParameter(SynthParameter(labelTuning).number(251))
    .addParameter(
      SynthParameter(labelTranspose)
        .type(CENTER_128)
        .number(241))
    .addParameter(SynthParameter(labelVolume).number(509));
}

Section SectionFactory::createOscillatorSection() {
  return Section(labelOscillators)
    .virtualSubSectionTitles({ oscSubTitles[0],
                               oscSubTitles[1],
                               oscSubTitles[2],
                               oscSubTitles[3] })
    .addParameter(
      SynthParameter(labelOscOnOff)
        .numbers({ 1, 2, 3, 4 })
        .max(1)
        .descriptions({ offOn[0],
                        offOn[1] }))
    .addParameter(
      SynthParameter(labelOscMode)
        .type(BITWISE)
        .number(6)
        .bitNumbers({ 0, 1, 2, 3 })
        .descriptions({ oscModePitch[0],
                        oscModePitch[1] }))
    .addParameter(
      SynthParameter(labelOscSync)
        .type(BITWISE)
        .number(5)
        .bitNumbers({ 0, 1, 2, 3 })
        .descriptions({ oscSync[0],
                        oscSync[1] }))
    .addParameter(
      SynthParameter(labelOscWaveform)
        .numbers({ 11, 12, 13, 14 })
        .max(8)
        .descriptions({ oscWaveformDescriptions[0],
                        oscWaveformDescriptions[1],
                        oscWaveformDescriptions[2],
                        oscWaveformDescriptions[3],
                        oscWaveformDescriptions[4],
                        oscWaveformDescriptions[5],
                        oscWaveformDescriptions[6],
                        oscWaveformDescriptions[7],
                        oscWaveformDescriptions[8] }))
    //3
    .addParameter(
      SynthParameter(labelOscPhase)
        .numbers({ 7, 8, 9, 10 })
        .max(3)
        .descriptions({ phaseDescriptions[0],
                        phaseDescriptions[1],
                        phaseDescriptions[2],
                        phaseDescriptions[3] }))
    //11
    .addParameter(
      SynthParameter(labelOscPW)
        .type(CENTER_128)
        .numbers({ 15, 16, 17, 18 }))
    //4
    .addParameter(
      SynthParameter(labelOscTranspose)
        .type(CENTER_128)
        .numbers({ 19, 20, 21, 22 }))
    //12
    .addParameter(
      SynthParameter(labelOscDetune)
        .type(CENTER_128)
        .numbers({ 23, 24, 25, 26 }))
    //5
    .addParameter(SynthParameter(sawstackDetune).numbers({ 285, 286, 287, 288 }))
    //13
    .addParameter(SynthParameter(labelOscDrift).numbers({ 260, 261, 262, 263 }))
    //6
    .addParameter(SynthParameter(labelOscLevel).numbers({ 27, 28, 29, 30 }))
    //14
    .addParameter(SynthParameter(labelOscPanLevelL).numbers({ 31, 33, 35, 37 }))
    //7
    .addParameter(SynthParameter(labelOscPanLevelR).numbers({ 32, 34, 36, 38 }))
    //15
    .addParameter(SynthParameter(labelOscVelSense).numbers({ 39, 40, 41, 42 }))
    //8
    .addParameter(SynthParameter(labelOscPMS).numbers({ 63, 64, 65, 66 }))
    //16
    .addParameter(SynthParameter(labelOscAMS).numbers({ 67, 68, 69, 70 }))

    // page 2
    //1
    .addParameter(SynthParameter(labelOscKeyLDepth).numbers({ 47, 48, 49, 50 }))
    //9
    .addParameter(SynthParameter(labelOscKeyLCurve).numbers({ 55, 56, 57, 58 }))
    //2
    .addParameter(SynthParameter(labelOscKeyRDepth).numbers({ 51, 52, 53, 54 }))
    //10
    .addParameter(SynthParameter(labelOscKeyRCurve).numbers({ 59, 60, 61, 62 }))
    //3
    .addParameter(SynthParameter(labeloscKeyBreakpoint).numbers({ 43, 44, 45, 46 }))
    //11
    .addParameter(SynthParameter(labelOscRingmod).number(271));
}

Section SectionFactory::createFilterSection() {
  return Section(labelFilters)
    .addParameter(SynthParameter(labelCutoff1).number(72))
    .addParameter(SynthParameter(labelResonance1).number(77))
    .addParameter(SynthParameter(labelCutoff2).number(78))
    .addParameter(SynthParameter(labelResonance2).number(79))
    .addParameter(
      SynthParameter("labelFilterType")
        .number(71)
        .max(21)
        .descriptions({ filterTypeDescriptions[0],
                        filterTypeDescriptions[1],
                        filterTypeDescriptions[2],
                        filterTypeDescriptions[3],
                        filterTypeDescriptions[4],
                        filterTypeDescriptions[5],
                        filterTypeDescriptions[6],
                        filterTypeDescriptions[7],
                        filterTypeDescriptions[8],
                        filterTypeDescriptions[9],
                        filterTypeDescriptions[10],
                        filterTypeDescriptions[11],
                        filterTypeDescriptions[12],
                        filterTypeDescriptions[13],
                        filterTypeDescriptions[14],
                        filterTypeDescriptions[15],
                        filterTypeDescriptions[16],
                        filterTypeDescriptions[17],
                        filterTypeDescriptions[18],
                        filterTypeDescriptions[19],
                        filterTypeDescriptions[20],
                        filterTypeDescriptions[21] }))
    //11
    .addParameter(
      SynthParameter(labelFilterVelocity)
        .type(CENTER_128)
        .number(73))
    //4
    .addParameter(
      SynthParameter(labelFilterTrack)
        .type(CENTER_128)
        .number(74))
    //12
    .addParameter(
      SynthParameter(labelFilterEGDepth)
        .type(CENTER_128)
        .number(75))
    //5
    .addParameter(
      SynthParameter(labelFilterEGVelocity)
        .type(CENTER_128)
        .number(76))
    //13
    .addParameter(
      SynthParameter(labelFilterVelocityReso)
        .type(CENTER_128)
        .number(276))
    //6
    .addParameter(
      SynthParameter(labelFilterTrackReso)
        .type(CENTER_128)
        .number(277))
    //14
    .addParameter(
      SynthParameter(labelFilterDrive)
        .number(275)
        .max(7))
    .addParameter(
      SynthParameter(labelFilterRouting)
        .number(278)
        .max(1)
        .descriptions({ lrModeDescriptions[0],
                        lrModeDescriptions[1] }));
}

Section SectionFactory::createEnvelopeSection() {
  return Section(labelEnvelopes)
    .virtualSubSectionTitles({ envSubTitles[0],
                               envSubTitles[1],
                               envSubTitles[2] })
    .addParameter(SynthParameter(labelEnvL0).numbers({ 82, 81, 80 }).type(CENTER_128))
    .addParameter(SynthParameter(labelEnvDelay).numbers({ 112, 111, 110 }))
    .addParameter(SynthParameter(labelEnvL1Attack).numbers({ 88, 86, 85 }).type(CENTER_128))
    .addParameter(SynthParameter(labelEnvR1Attack).numbers({ 117, 116, 115 }))
    .addParameter(SynthParameter(labelEnvL2Decay).numbers({ 92, 91, 90 }).type(CENTER_128))
    .addParameter(SynthParameter(labelEnvR2Decay).numbers({ 122, 121, 120 }))
    .addParameter(SynthParameter(labelEnvL3Sustain).numbers({ 97, 96, 95 }).type(CENTER_128))
    .addParameter(SynthParameter(labelEnvR3Sustain).numbers({ 127, 126, 125 }))
    .addParameter(SynthParameter(labelEnvL4Release1).numbers({ 102, 101, 100 }).type(CENTER_128))
    .addParameter(SynthParameter(labelEnvR4Release1).numbers({ 132, 131, 130 }))
    .addParameter(SynthParameter(labelEnvL5Release2).numbers({ 107, 106, 105 }).type(CENTER_128))
    .addParameter(SynthParameter(labelEnvR5Release2).numbers({ 137, 136, 135 }))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(""))

    .addParameter(
      SynthParameter(labelEnvLoop)
        .type(BITWISE)
        .number(145)
        .bitNumbers({ 0, 1, 6 })
        .descriptions({ envLoopDescriptions[0],
                        envLoopDescriptions[1] }))
    .addParameter(SynthParameter(""))
    .addParameter(
      SynthParameter(labelEnvLoopSegment)
        .type(BITWISE)
        .number(146)
        .bitNumbers({ 0, 1, 6 })
        .descriptions({ envLoopSegment[0],
                        envLoopSegment[1] }))
    .addParameter(SynthParameter(""))
    .addParameter(
      SynthParameter(labelEnvRestart)
        .type(BITWISE)
        .number(147)
        .bitNumbers({ 0, 1, 6 })
        .descriptions({ envRestart[0],
                        envRestart[1] }))
    .addParameter(SynthParameter(""))
    .addParameter(
      SynthParameter(labelEnvRange)
        .numbers({ 148, -1, -1 })
        .max(10))
    .addParameter(SynthParameter(""))
    .addParameter(
      SynthParameter("labelEnvVelocity")
        .numbers({ 149, -1, -1 })
        .max(10));
}

Section SectionFactory::createLFOSection() {
  return Section(labelLFO)
    //1
    .addParameter(
      SynthParameter(lfo1Wave)
        .number(160)
        .max(9)
        .descriptions({ lfoWaveDescriptions[0],
                        lfoWaveDescriptions[1],
                        lfoWaveDescriptions[2],
                        lfoWaveDescriptions[3],
                        lfoWaveDescriptions[4],
                        lfoWaveDescriptions[5],
                        lfoWaveDescriptions[6],
                        lfoWaveDescriptions[7],
                        lfoWaveDescriptions[8],
                        lfoWaveDescriptions[9] }))
    //9
    .addParameter(SynthParameter(lfo1Speed).number(161))
    //2
    .addParameter(SynthParameter(lfo1Range).number(166))
    //10
    .addParameter(
      SynthParameter(lfo1Sync)
        .number(162)
        .max(3)
        .descriptions({ lfoSyncDescriptions[0],
                        lfoSyncDescriptions[1],
                        lfoSyncDescriptions[2],
                        lfoSyncDescriptions[3] }))
    //3
    .addParameter(SynthParameter(lfo1Fade).number(163))
    //11
    .addParameter(SynthParameter(""))
    //4
    .addParameter(SynthParameter(lfo1DepthAmplitude).number(165))
    //12
    .addParameter(SynthParameter(lfo1DepthPitch).number(164))
    //5
    .addParameter(
      SynthParameter(lfo2Wave)
        .number(170)
        .max(9)
        .descriptions({ lfoWaveDescriptions[0],
                        lfoWaveDescriptions[1],
                        lfoWaveDescriptions[2],
                        lfoWaveDescriptions[3],
                        lfoWaveDescriptions[4],
                        lfoWaveDescriptions[5],
                        lfoWaveDescriptions[6],
                        lfoWaveDescriptions[7],
                        lfoWaveDescriptions[8],
                        lfoWaveDescriptions[9] }))
    //13
    .addParameter(SynthParameter(lfo2Speed).number(171))
    //6
    .addParameter(SynthParameter(lfo2Range).number(176))
    //14
    .addParameter(
      SynthParameter(lfo2Sync)
        .number(172)
        .max(3)
        .descriptions({ lfoSyncDescriptions[0],
                        lfoSyncDescriptions[1],
                        lfoSyncDescriptions[2],
                        lfoSyncDescriptions[3] }))
    //7
    .addParameter(SynthParameter(lfo2Fade).number(173))
    //15
    .addParameter(SynthParameter(""))
    //8
    .addParameter(SynthParameter(lfo2DepthPWM).number(174))
    //16
    .addParameter(SynthParameter(lfo2DepthFilter).number(175))

    //Page 2
    //1
    .addParameter(SynthParameter(pitchLFOAfter).number(180))
    //9
    .addParameter(SynthParameter(pitchLFOBreath).number(182))
    //2
    .addParameter(SynthParameter(pitchLFOWheel).number(181))
    //10
    .addParameter(SynthParameter(pitchLFOFoot).number(183))
    //3
    .addParameter(SynthParameter(PWLFOAfter).number(184))
    //11
    .addParameter(SynthParameter(PWLFOBreath).number(186))
    //4
    .addParameter(SynthParameter(PWLFOWheel).number(183))
    //12
    .addParameter(SynthParameter(PWLFOFoot).number(187))
    //5
    .addParameter(SynthParameter(filterLFOAfter).number(188))
    //9
    .addParameter(SynthParameter(filterLFOBreath).number(189))
    //2
    .addParameter(SynthParameter(filterLFOWheel).number(190))
    //10
    .addParameter(SynthParameter(filterLFOFoot).number(191))
    //3
    .addParameter(SynthParameter(ampLFOAfter).number(192))
    //11
    .addParameter(SynthParameter(ampLFOBreath).number(194))
    //4
    .addParameter(SynthParameter(ampLFOWheel).number(193))
    //12
    .addParameter(SynthParameter(ampLFOFoot).number(195));
}

Section SectionFactory::createEffectsSection() {
  return Section(labelEffects)
    .addSubSection(
      Section(labelEffectsMain)
        .addParameter(
          SynthParameter(effectsBandwidth)
            .number(340)
            .max(7)
            .descriptions({ filterPostDescriptions[0],
                            filterPostDescriptions[1],
                            filterPostDescriptions[2],
                            filterPostDescriptions[3],
                            filterPostDescriptions[4],
                            filterPostDescriptions[5],
                            filterPostDescriptions[6],
                            filterPostDescriptions[7] }))
        .addParameter(
          SynthParameter(effectsFXRouting)
            .number(508)
            .max(2)
            .descriptions({ fxRoutingDescriptions[0],
                            fxRoutingDescriptions[1],
                            fxRoutingDescriptions[2] }))
        .addParameter(
          SynthParameter(effectsBitCrusherDepth).number(380))
        .addParameter(
          SynthParameter(effectsDecimatorDepth).number(370))
        .addParameter(
          SynthParameter(effectsFilterHi).number(320))
        .addParameter(
          SynthParameter(effectsFilterLo).number(321)))
    .addSubSection(
      Section(effectsDistortion)
        .addParameter(
          SynthParameter("On or Off")
            .number(350)
            .max(1)
            .descriptions({ offOn[0],
                            offOn[1] }))
        .addParameter(
          SynthParameter(effectsType)
            .number(354)
            .max(3)
            .descriptions({ distortionTypeDescriptions[0],
                            distortionTypeDescriptions[1],
                            distortionTypeDescriptions[2],
                            distortionTypeDescriptions[3] }))
        .addParameter(SynthParameter(effectsGainPre).number(351))
        .addParameter(SynthParameter(effectsGainPost).number(352))
        .addParameter(
          SynthParameter(effectsFilterPost)
            .number(353)
            .max(7)
            .descriptions({ filterPostDescriptions[0],
                            filterPostDescriptions[1],
                            filterPostDescriptions[2],
                            filterPostDescriptions[3],
                            filterPostDescriptions[4],
                            filterPostDescriptions[5],
                            filterPostDescriptions[6],
                            filterPostDescriptions[7] })))
    .addSubSection(
      Section(effectsChorusFlanger)
        .addParameter(SynthParameter(effectsChorusDry).number(360))
        .addParameter(SynthParameter(effectsChorusWet).number(351))
        .addParameter(
          SynthParameter(effectsChorusMode)
            .number(362)
            .max(3)
            .descriptions({ lfoModeDescriptions[0],
                            lfoModeDescriptions[1],
                            lfoModeDescriptions[2],
                            lfoModeDescriptions[3] }))
        .addParameter(SynthParameter(effectsChorusSpeed).number(363))
        .addParameter(SynthParameter(effectsChorusDepth).number(364))
        .addParameter(SynthParameter(effectsChorusFeedback).number(365))

        .addParameter(SynthParameter(effectsChorusLRPhase).number(366).type(CENTER_128)))
    .addSubSection(
      Section(effectsPhaser)
        .addParameter(SynthParameter(effectsChorusDry).number(310))
        .addParameter(SynthParameter(effectsChorusWet).number(311))
        .addParameter(
          SynthParameter(effectsChorusMode)
            .number(312)
            .max(2)
            .descriptions({ monoStereo[0],
                            monoStereo[1],
                            monoStereo[2] }))
        .addParameter(SynthParameter(effectsChorusSpeed).number(314))
        .addParameter(SynthParameter(effectsChorusDepth).number(313))
        .addParameter(SynthParameter(effectsPhaserOffset).number(316))
        .addParameter(
          SynthParameter(effectsPhaserStages)
            .number(317)
            .min(4)
            .max(12))
        .addParameter(SynthParameter(effectsChorusFeedback).number(315))
        .addParameter(SynthParameter(effectsChorusLRPhase).number(318).type(CENTER_128)))
    .addSubSection(
      Section(effectsDelay)
        .addParameter(SynthParameter(effectsChorusDry).number(300))
        .addParameter(SynthParameter(effectsChorusWet).number(301))
        .addParameter(
          SynthParameter(effectsChorusMode)
            .number(302)
            .max(2)
            .descriptions({ monoStereo[0],
                            monoStereo[1],
                            monoStereo[2] }))
        .addParameter(SynthParameter(effectsDelayTime).number(303))
        .addParameter(SynthParameter(effectsChorusFeedback).number(304))
        .addParameter(SynthParameter(effectsDelayTempo).number(307))
        .addParameter(SynthParameter(effectsDelayHI).number(305))
        .addParameter(SynthParameter(effectsDelayLO).number(306))
        .addParameter(SynthParameter(effectsDelayMultiplier).number(308).min(1))
        .addParameter(SynthParameter(effectsDelayDivider).number(309).min(1))
        .addParameter(SynthParameter(effectsDelayModSpeed).number(298))
        .addParameter(SynthParameter(effectsDelayModDepth).number(299))
        .addParameter(
          SynthParameter(effectsDelaySmear)
            .number(291)
            .max(7)
            .descriptions({ smearDescriptions[0],
                            smearDescriptions[1],
                            smearDescriptions[2],
                            smearDescriptions[3],
                            smearDescriptions[4],
                            smearDescriptions[5],
                            smearDescriptions[6],
                            smearDescriptions[7] }))
        .addParameter(
          SynthParameter(effectsDelay2x)
            .number(291)
            .max(1)
            .descriptions({ xOn[0],
                            xOn[1] })))
    .addSubSection(
      Section(effectsReverb)
        .addParameter(SynthParameter(effectsChorusDry).number(390))
        .addParameter(SynthParameter(effectsChorusWet).number(291))
        .addParameter(
          SynthParameter(effectsChorusMode)
            .number(392)
            .max(1)
            .descriptions({ reverbModeDescriptions[0],
                            reverbModeDescriptions[1] }))
        .addParameter(SynthParameter(effectsReverbDecay).number(393))
        .addParameter(SynthParameter(effectsReverbDamping).number(394))
        .addParameter(SynthParameter(effectsReverbHPF).number(397))
        .addParameter(SynthParameter(effectsDelayModSpeed).number(395))
        .addParameter(SynthParameter(effectsDelayModSpeed).number(396))

        )
    .addSubSection(
      Section(effectsGate)
        .addParameter(
          SynthParameter(effectsGateOn)
            .number(385)
            .max(1)
            .descriptions({ offOn[0],
                            offOn[1] }))
        .addParameter(
          SynthParameter(effectsGateCurve)
            .number(386)
            .max(1)
            .descriptions({ gateCurveDescriptions[0],
                            gateCurveDescriptions[1] }))
        .addParameter(SynthParameter(effectsGateAttack).number(387))
        .addParameter(SynthParameter(effectsGateRelease).number(388)))
    .addSubSection(
      Section(effectsReflections)
        .addParameter(SynthParameter(effectsChorusDry).number(294))
        .addParameter(SynthParameter(effectsChorusWet).number(295))
        .addParameter(SynthParameter(effectsReflectionsRoom).number(296).max(31))
        .addParameter(SynthParameter(effectsReflectionsTaps).number(293).max(32))
        .addParameter(SynthParameter(effectsChorusFeedback).number(297)));
}

Section SectionFactory::createPatchSection() {
  return Section(namingPatch)
    .addParameter(SynthParameter(naming1).asciiCharacterType(480))
    .addParameter(SynthParameter(naming9).asciiCharacterType(488))
    .addParameter(SynthParameter(naming2).asciiCharacterType(481))
    .addParameter(SynthParameter(naming10).asciiCharacterType(489))
    .addParameter(SynthParameter(naming3).asciiCharacterType(482))
    .addParameter(SynthParameter(naming11).asciiCharacterType(490))
    .addParameter(SynthParameter(naming4).asciiCharacterType(483))
    .addParameter(SynthParameter(naming12).asciiCharacterType(491))
    .addParameter(SynthParameter(naming5).asciiCharacterType(484))
    .addParameter(SynthParameter(naming13).asciiCharacterType(492))
    .addParameter(SynthParameter(naming6).asciiCharacterType(485))
    .addParameter(SynthParameter(naming14).asciiCharacterType(493))
    .addParameter(SynthParameter(naming7).asciiCharacterType(486))
    .addParameter(SynthParameter(naming15).asciiCharacterType(494))
    .addParameter(SynthParameter(naming8).asciiCharacterType(487))
    .addParameter(SynthParameter(naming16).asciiCharacterType(495))
    .addParameter(SynthParameter(naming17).asciiCharacterType(496))
    .addParameter(SynthParameter(naming25).asciiCharacterType(504))
    .addParameter(SynthParameter(naming18).asciiCharacterType(497))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(naming19).asciiCharacterType(498))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(naming20).asciiCharacterType(499))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(naming21).asciiCharacterType(500))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(naming22).asciiCharacterType(501))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(naming23).asciiCharacterType(502))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(naming24).asciiCharacterType(503));
}

Section SectionFactory::createSequencerSection() {
  return Section(sequencer)
    .addSubSection(
      Section(sequencerMain)
        .addParameter(
          SynthParameter(sequencerOn)
            .number(428)
            .max(1)
            .descriptions({ offOn[0],
                            offOn[1] }))
        .addParameter(SynthParameter(sequencerSteps).number(430).max(16))
        .addParameter(SynthParameter(effectsDelayTempo).number(431))
        .addParameter(SynthParameter(effectsDelayMultiplier).number(432).min(1))
        .addParameter(SynthParameter(labelFilterVelocity).number(429))
        .addParameter(SynthParameter(labelTranspose).number(433))
        .addParameter(SynthParameter(""))
        .addParameter(SynthParameter(""))
        .addParameter(SynthParameter(""))
        .addParameter(SynthParameter(""))
        .addParameter(SynthParameter(""))
        .addParameter(SynthParameter(""))
        .addParameter(SynthParameter(""))
        .addParameter(SynthParameter(""))
        .addParameter(SynthParameter(""))
        .addParameter(SynthParameter(""))

        )
    .addSubSection(
      Section(sequencerSteps)
        .addParameter(SynthParameter(sequencerStep1).number(434).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep9).number(442).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep2).number(435).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep10).number(443).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep3).number(436).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep11).number(444).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep4).number(437).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep12).number(445).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep5).number(438).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep13).number(446).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep6).number(439).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep14).number(447).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep7).number(440).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep15).number(448).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep8).number(441).type(MIDI_NOTE))
        .addParameter(SynthParameter(sequencerStep16).number(449).type(MIDI_NOTE))
    );
}

Section SectionFactory::createExternalControlsSection() {
  return Section(labelExternalCtrls)
    .addSubSection(
      Section(labelExternalCtrls)
        //1
        .addParameter(
          SynthParameter(extPitchTemperature)
            .number(220)
            .type(CENTER_128))
        //9
        .addParameter(
          SynthParameter(extPWMTemperature)
            .number(223)
            .type(CENTER_128))
        //2
        .addParameter(
          SynthParameter(extPitchCV1)
            .number(221)
            .type(CENTER_128)

            )
        //10
        .addParameter(
          SynthParameter(extPWMCV1)
            .number(224)
            .type(CENTER_128))
        //3
        .addParameter(
          SynthParameter(extPitchCV2)
            .number(222)
            .type(CENTER_128)

            )
        //11
        .addParameter(
          SynthParameter(extPWMCV2)
            .number(225)
            .type(CENTER_128))
        //4
        .addParameter(SynthParameter(extPitchRandom).number(203))
        //12
        .addParameter(SynthParameter(""))
        //5
        .addParameter(
          SynthParameter(extFilterTemperature)
            .number(226)
            .type(CENTER_128))
        //13
        .addParameter(SynthParameter(extVolumeTemperature).number(228))
        //6
        .addParameter(
          SynthParameter(extFilterCV1)
            .number(227)
            .type(CENTER_128))
        //14
        .addParameter(SynthParameter(extVolumeCV1).number(230))
        //7
        .addParameter(
          SynthParameter(extFilterCV2)
            .number(228)
            .type(CENTER_128))
        //15
        .addParameter(SynthParameter(extVolumeCV1).number(231)))
    .addSubSection(
      Section(extLFOSModulation)
        //1
        .addParameter(SynthParameter(pitchLFOAfter).number(180))
        //9
        .addParameter(SynthParameter(pitchLFOBreath).number(182))
        //2
        .addParameter(SynthParameter(pitchLFOWheel).number(181))
        //10
        .addParameter(SynthParameter(pitchLFOFoot).number(183))
        //3
        .addParameter(SynthParameter(PWLFOAfter).number(184))
        //11
        .addParameter(SynthParameter(PWLFOBreath).number(186))
        //4
        .addParameter(SynthParameter(PWLFOWheel).number(183))
        //12
        .addParameter(SynthParameter(PWLFOFoot).number(187))
        //5
        .addParameter(SynthParameter(filterLFOAfter).number(188))
        //9
        .addParameter(SynthParameter(filterLFOBreath).number(189))
        //2
        .addParameter(SynthParameter(filterLFOWheel).number(190))
        //10
        .addParameter(SynthParameter(filterLFOFoot).number(191))
        //3
        .addParameter(SynthParameter(ampLFOAfter).number(192))
        //11
        .addParameter(SynthParameter(ampLFOBreath).number(194))
        //4
        .addParameter(SynthParameter(ampLFOWheel).number(193))
        //12
        .addParameter(SynthParameter(ampLFOFoot).number(195)));
}

Section SectionFactory::createPerformanceControlsSection() {
  return Section(labelPerfControls)
    .addParameter(SynthParameter(perfControls70).performanceControlType(400, 401))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(perfControls71).performanceControlType(402, 403))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(perfControls72).performanceControlType(404, 405))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(perfControls73).performanceControlType(406, 407))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(perfControls74).performanceControlType(408, 409))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(perfControls75).performanceControlType(410, 411))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(perfControls76).performanceControlType(412, 413))
    .addParameter(SynthParameter(""))
    .addParameter(SynthParameter(perfControls77).performanceControlType(414, 415));
}

Section SectionFactory::createMIDIModSection() {
  return Section(labelMIDIMod)
    .addSubSection(
      Section(labelMIDIModulation)
        //1
        .addParameter(
          SynthParameter(pitchAfter)
            .number(200)
            .type(CENTER_128))
        //9
        .addParameter(
          SynthParameter(PWMAfter)
            .number(204)
            .type(CENTER_128))
        //2
        .addParameter(
          SynthParameter(pitchBreath)
            .number(201)
            .type(CENTER_128))
        //10
        .addParameter(
          SynthParameter(PWMBreath)
            .number(206)
            .type(CENTER_128))
        //3
        .addParameter(
          SynthParameter(pitchFoot)
            .number(202)
            .type(CENTER_128))
        //11
        .addParameter(
          SynthParameter(PWMFoot)
            .number(207)
            .type(CENTER_128))
        //4
        .addParameter(SynthParameter(""))
        //12
        .addParameter(
          SynthParameter(PWMWheel)
            .number(205)
            .type(CENTER_128))
        //5
        .addParameter(
          SynthParameter(filterAftertouch)
            .number(208)
            .type(CENTER_128))
        //13
        .addParameter(SynthParameter(volumeAftertouch).number(212))
        //6
        .addParameter(
          SynthParameter(filterBreath)
            .number(210)
            .type(CENTER_128))
        //14
        .addParameter(SynthParameter(midiMODBreath).number(214))
        //7
        .addParameter(
          SynthParameter(filterFoot)
            .number(211)
            .type(CENTER_128))
        //15
        .addParameter(SynthParameter(volumeFoot).number(215))
        //8
        .addParameter(
          SynthParameter(filterWheel)
            .number(209)
            .type(CENTER_128))
        //16
        .addParameter(SynthParameter(volumeWheel).number(213)))
    .addSubSection(
      Section("LFOs Modulation")
        //1
        .addParameter(SynthParameter(pitchLFOAfter).number(180))
        //9
        .addParameter(SynthParameter(pitchLFOBreath).number(182))
        //2
        .addParameter(SynthParameter(pitchLFOWheel).number(181))
        //10
        .addParameter(SynthParameter(pitchLFOFoot).number(183))
        //3
        .addParameter(SynthParameter(PWLFOAfter).number(184))
        //11
        .addParameter(SynthParameter(PWLFOBreath).number(186))
        //4
        .addParameter(SynthParameter(PWLFOWheel).number(183))
        //12
        .addParameter(SynthParameter(PWLFOFoot).number(187))
        //5
        .addParameter(SynthParameter(filterLFOAfter).number(188))
        //9
        .addParameter(SynthParameter(filterLFOBreath).number(189))
        //2
        .addParameter(SynthParameter(filterLFOWheel).number(190))
        //10
        .addParameter(SynthParameter(filterLFOFoot).number(191))
        //3
        .addParameter(SynthParameter(ampLFOAfter).number(192))
        //11
        .addParameter(SynthParameter(ampLFOBreath).number(194))
        //4
        .addParameter(SynthParameter(ampLFOWheel).number(193))
        //12
        .addParameter(SynthParameter(ampLFOFoot).number(195)));
}

Section SectionFactory::createGlobalSection() {
  return Section(labelGlobal)
    .addParameter(
      SynthParameter(labelTranspose)
        .type(CENTER_128)
        .number(241))
    .addParameter(SynthParameter(labelOscRingmod).number(271))
    .addParameter(SynthParameter(globalBendUp).number(242))
    .addParameter(SynthParameter(globalBendDown).number(243))
    .addParameter(
      SynthParameter(labelLegatoMode)
        .number(244)
        .max(1)
        .descriptions({ legatoDescriptions[0],
                        legatoDescriptions[1] }))
    .addParameter(SynthParameter(""))
    .addParameter(
      SynthParameter(labelGlide)
        .number(245)
        .max(2)
        .descriptions({ glideDescriptions[0],
                        glideDescriptions[1],
                        glideDescriptions[2] }))
    .addParameter(SynthParameter(labelGlideTime).number(246))
    .addParameter(SynthParameter(globalVelocityOffset).number(249))
    .addParameter(SynthParameter(labelTuning).number(251))
    .addParameter(SynthParameter(globalTemperatureOffset).number(239))
    .addParameter(SynthParameter(labelVolume).number(509))
    .addParameter(SynthParameter(globalPanning).number(247).type(CENTER_128))
    .addParameter(
      SynthParameter(globalGainPre)
        .number(510)
        .max(3)
        .descriptions({ gainDbDescriptions[0],
                        gainDbDescriptions[1],
                        gainDbDescriptions[2],
                        gainDbDescriptions[3] }))
    .addParameter(
      SynthParameter(globalGainPost)
        .number(511)
        .max(3)
        .descriptions({ gainDbDescriptions[0],
                        gainDbDescriptions[1],
                        gainDbDescriptions[2],
                        gainDbDescriptions[3] }));
}
