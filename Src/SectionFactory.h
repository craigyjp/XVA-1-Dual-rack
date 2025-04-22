#ifndef XVA1USERINTERFACE_SECTIONFACTORY_H
#define XVA1USERINTERFACE_SECTIONFACTORY_H

#include "Section.h"

class SectionFactory {
public:
    Section createDefaultSection();

    Section createEffectsSection();

    Section createOscillatorSection();

    Section createEnvelopeSection();

    Section createLFOSection();

    Section createFilterSection();

    Section createPatchSection();

    Section createExternalControlsSection();

    Section createPerformanceControlsSection();

    Section createSequencerSection();

    Section createMIDIModSection();

    Section createGlobalSection();
};

FLASHMEM static const char oscSubTitles0[] = "Oscillator 1";
FLASHMEM static const char oscSubTitles1[] = "Oscillator 2";
FLASHMEM static const char oscSubTitles2[] = "Oscillator 3";
FLASHMEM static const char oscSubTitles3[] = "Oscillator 4";

FLASHMEM static const char* const oscSubTitles[] = { 
         oscSubTitles0,
         oscSubTitles1,
         oscSubTitles2,
         oscSubTitles3
};

// Menu Titles

FLASHMEM static const char labelDefault[] = "Default";
FLASHMEM static const char labelOscillators[] = "Oscillators";
FLASHMEM static const char labelFilters[] = "Filters";
FLASHMEM static const char labelEnvelopes[] = "Envelopes";
FLASHMEM static const char labelLFO[] = "LFO";
FLASHMEM static const char labelEffects[] = "Effects";
FLASHMEM static const char labelPerfControls[] = "Performance Controls";
FLASHMEM static const char labelMIDIMod[] = "MIDI Mod";
FLASHMEM static const char labelGlobal[] = "Global";


// Sub menus

FLASHMEM static const char envSubTitles0[] = "AMP";
FLASHMEM static const char envSubTitles1[] = "CUTOFF";
FLASHMEM static const char envSubTitles2[] = "PITCH";

FLASHMEM static const char* const envSubTitles[] = { 
        envSubTitles0,
        envSubTitles1,
        envSubTitles0
};

// Parameter Sections
// Default
FLASHMEM static const char labelCutoff1[] = "Cutoff 1";
FLASHMEM static const char labelResonance1[] = "Resonance 1";
FLASHMEM static const char labelCutoff2[] = "Cutoff 2";
FLASHMEM static const char labelResonance2[] = "Resonance 2";
FLASHMEM static const char labelArpMode[] = "ARP Mode";
FLASHMEM static const char labelArpTempo[] = "ARP Tempo";
FLASHMEM static const char labelMultiplier[] = "Multiplier";
FLASHMEM static const char labelOctaves[] = "Octaves";
FLASHMEM static const char labelSequencer[] = "Sequencer";
FLASHMEM static const char labelSequencerTempo[] = "Sequencer Tempo";
FLASHMEM static const char labelGlide[] = "Glide";
FLASHMEM static const char labelGlideTime[] = "Glide Time";
FLASHMEM static const char labelLegatoMode[] = "Legato Mode";
FLASHMEM static const char labelTuning[] = "Tuning";
FLASHMEM static const char labelTranspose[] = "Transpose";
FLASHMEM static const char labelVolume[] = "Volume";

// Ocillators
FLASHMEM static const char labelOscOnOff[] = "On or Off";
FLASHMEM static const char labelOscMode[] = "Mode";
FLASHMEM static const char labelOscSync[] = "Sync";
FLASHMEM static const char labelOscWaveform[] = "Waveform";
FLASHMEM static const char labelOscPhase[] = "Phase";
FLASHMEM static const char labelOscPW[] = "Pulse Width";
FLASHMEM static const char labelOscTranspose[] = "Transpose";
FLASHMEM static const char labelOscDetune[] = "Detune";
FLASHMEM static const char sawstackDetune[] = "Sawstack Detune";
FLASHMEM static const char labelOscDrift[] = "Drift";
FLASHMEM static const char labelOscLevel[] = "Oscillator Level";
FLASHMEM static const char labelOscPanLevelL[] = "Panning Level L";
FLASHMEM static const char labelOscPanLevelR[] = "Panning Level R";
FLASHMEM static const char labelOscVelSense[] = "Velocity Sens.";
FLASHMEM static const char labelOscPMS[] = "PMS";
FLASHMEM static const char labelOscAMS[] = "AMS";
FLASHMEM static const char labelOscKeyLDepth[] = "Key L Depth";
FLASHMEM static const char labelOscKeyLCurve[] = "key L Curve";
FLASHMEM static const char labelOscKeyRDepth[] = "Key R Depth";
FLASHMEM static const char labelOscKeyRCurve[] = "Key R Curve";
FLASHMEM static const char labeloscKeyBreakpoint[] = "Key Breakpoint";
FLASHMEM static const char labelOscRingmod[] = "Ring Mod";

// Filters
FLASHMEM static const char labelFilterType[] = "Type";
FLASHMEM static const char labelFilterVelocity[] = "Velocity";
FLASHMEM static const char labelFilterTrack[] = "KBD Track";
FLASHMEM static const char labelFilterEGDepth[] = "EG Depth";
FLASHMEM static const char labelFilterEGVelocity[] = "EG Velocity";
FLASHMEM static const char labelFilterVelocityReso[] = "Velocity RESO";
FLASHMEM static const char labelFilterTrackReso[] = "KBD Track RESO";
FLASHMEM static const char labelFilterDrive[] = "Drive";
FLASHMEM static const char labelFilterRouting[] = "Routing";

//Envelopes
FLASHMEM static const char labelEnvL0[] = "L0: Start";
FLASHMEM static const char labelEnvDelay[] = "Delay";
FLASHMEM static const char labelEnvL1Attack[] = "L1: Attack";
FLASHMEM static const char labelEnvR1Attack[] = "R1: Attack";
FLASHMEM static const char labelEnvL2Decay[] = "L2: Decay";
FLASHMEM static const char labelEnvR2Decay[] = "R2: Decay";
FLASHMEM static const char labelEnvL3Sustain[] = "L3: Sustain";
FLASHMEM static const char labelEnvR3Sustain[] = "R3: Sustain";
FLASHMEM static const char labelEnvL4Release1[] = "L4: Release 1";
FLASHMEM static const char labelEnvR4Release1[] = "R4: Release 1";
FLASHMEM static const char labelEnvL5Release2[] = "L5: Release 2";
FLASHMEM static const char labelEnvR5Release2[] = "R5: Release 2";
FLASHMEM static const char labelEnvLoop[] = "EG Loop";
FLASHMEM static const char labelEnvLoopSegment[] = "EG Loop Segment";
FLASHMEM static const char labelEnvRestart[] = "EG Restart From";
FLASHMEM static const char labelEnvRange[] = "Range";
FLASHMEM static const char labelEnvVelocity[] = "Velocity";

// LFO
FLASHMEM static const char lfo1Wave[] = "LFO 1 Wave";
FLASHMEM static const char lfo1Speed[] = "LFO 1 Speed";
FLASHMEM static const char lfo1Range[] = "LFO 1 Range";
FLASHMEM static const char lfo1Sync[] = "LFO 1 Sync";
FLASHMEM static const char lfo1Fade[] = "LFO 1 Fade";
FLASHMEM static const char lfo1DepthAmplitude[] = "LFO 1 Depth Amplitude";
FLASHMEM static const char lfo1DepthPitch[] = "LFO 1 Depth Pitch";
FLASHMEM static const char lfo2Wave[] = "LFO 2 Wave";
FLASHMEM static const char lfo2Speed[] = "LFO 2 Speed";
FLASHMEM static const char lfo2Range[] = "LFO 2 Range";
FLASHMEM static const char lfo2Sync[] = "LFO 2 Sync";
FLASHMEM static const char lfo2Fade[] = "LFO 2 Fade";
FLASHMEM static const char lfo2DepthPWM[] = "LFO 2 Depth PWM";
FLASHMEM static const char lfo2DepthFilter[] = "LFO 2 Depth Filter";

FLASHMEM static const char pitchLFOAfter[] = "Pitch LFO Aftertouch";
FLASHMEM static const char PWLFOAfter[] = "PW LFO Aftertouch";
FLASHMEM static const char filterLFOAfter[] = "Filter LFO Aftertouch";
FLASHMEM static const char ampLFOAfter[] = "AMP LFO Aftertouch";

FLASHMEM static const char pitchLFOBreath[] = "Pitch LFO Breath";
FLASHMEM static const char PWLFOBreath[] = "PW LFO Breath";
FLASHMEM static const char filterLFOBreath[] = "Filter LFO Breath";
FLASHMEM static const char ampLFOBreath[] = "AMP LFO Breath";

FLASHMEM static const char pitchLFOWheel[] = "Pitch LFO Wheel";
FLASHMEM static const char PWLFOWheel[] = "PW LFO Wheel";
FLASHMEM static const char filterLFOWheel[] = "Filter LFO Wheel";
FLASHMEM static const char ampLFOWheel[] = "AMP LFO Wheel";

FLASHMEM static const char pitchLFOFoot[] = "Pitch LFO Foot";
FLASHMEM static const char PWLFOFoot[] = "PW LFO Foot";
FLASHMEM static const char filterLFOFoot[] = "Filter LFO Foot";
FLASHMEM static const char ampLFOFoot[] = "AMP LFO Foot";

//Effects
FLASHMEM static const char labelEffectsMain[] = "Main";
FLASHMEM static const char effectsBandwidth[] = "Bandwidth";
FLASHMEM static const char effectsFXRouting[] = "FX Routing";
FLASHMEM static const char effectsBitCrusherDepth[] = "Bitcrusher Depth";
FLASHMEM static const char effectsDecimatorDepth[] = "Decimator Depth";
FLASHMEM static const char effectsFilterHi[] = "Filter HI";
FLASHMEM static const char effectsFilterLo[] = "Filter LO";

FLASHMEM static const char effectsDistortion[] = "Distortion";
FLASHMEM static const char effectsType[] = "Type";
FLASHMEM static const char effectsGainPre[] = "Gain PRE";
FLASHMEM static const char effectsGainPost[] = "Gain POST";
FLASHMEM static const char effectsFilterPost[] = "Filter POST";

FLASHMEM static const char effectsChorusFlanger[] = "Chorus/Flanger";
FLASHMEM static const char effectsChorusDry[] = "DRY";
FLASHMEM static const char effectsChorusWet[] = "WET";
FLASHMEM static const char effectsChorusMode[] = "Mode";
FLASHMEM static const char effectsChorusSpeed[] = "Speed";
FLASHMEM static const char effectsChorusDepth[] = "Depth";
FLASHMEM static const char effectsChorusFeedback[] = "feedback";
FLASHMEM static const char effectsChorusLRPhase[] = "LR Phase";

FLASHMEM static const char effectsPhaser[] = "Phaser";
FLASHMEM static const char effectsPhaserOffset[] = "Offset";
FLASHMEM static const char effectsPhaserStages[] = "Stages";

FLASHMEM static const char effectsDelay[] = "Delay";
FLASHMEM static const char effectsDelayTime[] = "Time";
FLASHMEM static const char effectsDelayTempo[] = "Tempo";
FLASHMEM static const char effectsDelayHI[] = "HI";
FLASHMEM static const char effectsDelayLO[] = "LO";
FLASHMEM static const char effectsDelayMultiplier[] = "Multiplier";
FLASHMEM static const char effectsDelayDivider[] = "Divider";
FLASHMEM static const char effectsDelayModSpeed[] = "Modulation Speed";
FLASHMEM static const char effectsDelayModDepth[] = "Modulation Depth";
FLASHMEM static const char effectsDelaySmear[] = "Smear";
FLASHMEM static const char effectsDelay2x[] = "2x";

FLASHMEM static const char effectsReverb[] = "Reverb";
FLASHMEM static const char effectsReverbDecay[] = "Decay";
FLASHMEM static const char effectsReverbDamping[] = "Damping";
FLASHMEM static const char effectsReverbHPF[] = "HPF";

FLASHMEM static const char effectsGate[] = "Gate";
FLASHMEM static const char effectsGateOn[] = "On or Off";
FLASHMEM static const char effectsGateCurve[] = "Curve";
FLASHMEM static const char effectsGateAttack[] = "Attack";
FLASHMEM static const char effectsGateRelease[] = "Release";

FLASHMEM static const char effectsReflections[] = "Early Reflections";
FLASHMEM static const char effectsReflectionsRoom[] = "Room";
FLASHMEM static const char effectsReflectionsTaps[] = "taps";

// Naming
FLASHMEM static const char namingPatch[] = "Patch";
FLASHMEM static const char naming1[] = "Name 1";
FLASHMEM static const char naming2[] = "Name 2";
FLASHMEM static const char naming3[] = "Name 3";
FLASHMEM static const char naming4[] = "Name 4";
FLASHMEM static const char naming5[] = "Name 5";
FLASHMEM static const char naming6[] = "Name 6";
FLASHMEM static const char naming7[] = "Name 7";
FLASHMEM static const char naming8[] = "Name 8";
FLASHMEM static const char naming9[] = "Name 9";
FLASHMEM static const char naming10[] = "Name 10";
FLASHMEM static const char naming11[] = "Name 11";
FLASHMEM static const char naming12[] = "Name 12";
FLASHMEM static const char naming13[] = "Name 13";
FLASHMEM static const char naming14[] = "Name 14";
FLASHMEM static const char naming15[] = "Name 15";
FLASHMEM static const char naming16[] = "Name 16";
FLASHMEM static const char naming17[] = "Name 17";
FLASHMEM static const char naming18[] = "Name 18";
FLASHMEM static const char naming19[] = "Name 19";
FLASHMEM static const char naming20[] = "Name 20";
FLASHMEM static const char naming21[] = "Name 21";
FLASHMEM static const char naming22[] = "Name 22";
FLASHMEM static const char naming23[] = "Name 23";
FLASHMEM static const char naming24[] = "Name 24";
FLASHMEM static const char naming25[] = "Name 24";

// Sequencer
FLASHMEM static const char sequencer[] = "Sequencer";
FLASHMEM static const char sequencerMain[] = "Main";
FLASHMEM static const char sequencerOn[] = "On or Off";
FLASHMEM static const char sequencerSteps[] = "Steps";
FLASHMEM static const char sequencerStep1[] = "Step 1";
FLASHMEM static const char sequencerStep2[] = "Step 2";
FLASHMEM static const char sequencerStep3[] = "Step 3";
FLASHMEM static const char sequencerStep4[] = "Step 4";
FLASHMEM static const char sequencerStep5[] = "Step 5";
FLASHMEM static const char sequencerStep6[] = "Step 6";
FLASHMEM static const char sequencerStep7[] = "Step 7";
FLASHMEM static const char sequencerStep8[] = "Step 8";
FLASHMEM static const char sequencerStep9[] = "Step 9";
FLASHMEM static const char sequencerStep10[] = "Step 10";
FLASHMEM static const char sequencerStep11[] = "Step 11";
FLASHMEM static const char sequencerStep12[] = "Step 12";
FLASHMEM static const char sequencerStep13[] = "Step 13";
FLASHMEM static const char sequencerStep14[] = "Step 14";
FLASHMEM static const char sequencerStep15[] = "Step 15";
FLASHMEM static const char sequencerStep16[] = "Step 16";

// External Controls
FLASHMEM static const char labelExternalCtrls[] = "External Ctrls";
FLASHMEM static const char extPitchTemperature[] = "Pitch Temperature";
FLASHMEM static const char extPWMTemperature[] = "PWM temperature";
FLASHMEM static const char extPitchCV1[] = "Pitch CV-1";
FLASHMEM static const char extPitchCV2[] = "Pitch CV-2";
FLASHMEM static const char extPWMCV1[] = "PWM CV-1";
FLASHMEM static const char extPWMCV2[] = "PWM CV-2";
FLASHMEM static const char extPitchRandom[] = "Pitch Random";
FLASHMEM static const char extFilterTemperature[] = "Filter Temperature";
FLASHMEM static const char extVolumeTemperature[] = "Volume Temperature";
FLASHMEM static const char extFilterCV1[] = "Filter CV-1";
FLASHMEM static const char extFilterCV2[] = "Filter CV-2";
FLASHMEM static const char extVolumeCV1[] = "Volume CV-1";
FLASHMEM static const char extVolumeCV2[] = "Volume CV-2";
FLASHMEM static const char extLFOSModulation[] = "LFOs Modulation";

// MIDI Perf Controls
FLASHMEM static const char perfControls70[] = "MIDI CC 70";
FLASHMEM static const char perfControls71[] = "MIDI CC 71";
FLASHMEM static const char perfControls72[] = "MIDI CC 72";
FLASHMEM static const char perfControls73[] = "MIDI CC 73";
FLASHMEM static const char perfControls74[] = "MIDI CC 74";
FLASHMEM static const char perfControls75[] = "MIDI CC 75";
FLASHMEM static const char perfControls76[] = "MIDI CC 76";
FLASHMEM static const char perfControls77[] = "MIDI CC 77";

// MIDI Modulation
FLASHMEM static const char labelMIDIModulation[] = "MIDI Modulation";
FLASHMEM static const char pitchAfter[] = "Pitch Aftertouch";
FLASHMEM static const char PWMAfter[] = "PWM Aftertouch";
FLASHMEM static const char pitchBreath[] = "Pitch Breath";
FLASHMEM static const char PWMBreath[] = "PWM Breath";
FLASHMEM static const char pitchFoot[] = "Pitch Foot";
FLASHMEM static const char PWMFoot[] = "PWM Foot";
FLASHMEM static const char PWMWheel[] = "PWM Wheel";
FLASHMEM static const char filterAftertouch[] = "Filter Aftertouch";
FLASHMEM static const char volumeAftertouch[] = "Volume Aftertouch";
FLASHMEM static const char filterBreath[] = "Filter Breath";
FLASHMEM static const char midiMODBreath[] = "Volume Breath";
FLASHMEM static const char filterFoot[] = "Filter Foot";
FLASHMEM static const char volumeFoot[] = "Volume Foot";
FLASHMEM static const char filterWheel[] = "Filter Wheel";
FLASHMEM static const char volumeWheel[] = "Volume Wheel";

// Global
FLASHMEM static const char globalBendUp[] = "Bend Up";
FLASHMEM static const char globalBendDown[] = "Bend Down";
FLASHMEM static const char globalVelocityOffset[] = "Velocity Offset";
FLASHMEM static const char globalTemperatureOffset[] = "Temperature Offset";
FLASHMEM static const char globalPanning[] = "Panning";
FLASHMEM static const char globalGainPre[] = "Gain Pre-FX";
FLASHMEM static const char globalGainPost[] = "Gain Post-FX";

// Parameters

FLASHMEM static const char xOn0[] = "Off";
FLASHMEM static const char xOn1[] = "2x Delay";

FLASHMEM static const char* const xOn[] = {
        xOn0,
        xOn1
};

FLASHMEM static const char oscSync0[] = "Free running";
FLASHMEM static const char oscSync1[] = "Restart on Key-ON";

FLASHMEM static const char* const oscSync[] = {
        oscSync0,
        oscSync1
};

FLASHMEM static const char envRestart0[] = "L5: Decay";
FLASHMEM static const char envRestart1[] = "L0: Start";

FLASHMEM static const char* const envRestart[] = {
        envRestart0,
        envRestart1
};

FLASHMEM static const char envLoopSegment0[] = "L0: Attack";
FLASHMEM static const char envLoopSegment1[] = "L5: Decay";

FLASHMEM static const char* const envLoopSegment[] = {
        envLoopSegment0,
        envLoopSegment1
};

FLASHMEM static const char envLoopDescriptions0[] = "Normal";
FLASHMEM static const char envLoopDescriptions1[] = "Loop";

FLASHMEM static const char* const envLoopDescriptions[] = {
        envLoopDescriptions0,
        envLoopDescriptions1
};

FLASHMEM static const char oscModePitch0[] = "KeyTrack";
FLASHMEM static const char oscModePitch1[] = "FixedPitch";

FLASHMEM static const char* const oscModePitch[] = {
        oscModePitch0,
        oscModePitch1
};

FLASHMEM static const char oscWaveformDescriptions0[] = "Saw up";
FLASHMEM static const char oscWaveformDescriptions1[] = "Saw down";
FLASHMEM static const char oscWaveformDescriptions2[] = "Square";
FLASHMEM static const char oscWaveformDescriptions3[] = "Triangle";
FLASHMEM static const char oscWaveformDescriptions4[] = "Sine";
FLASHMEM static const char oscWaveformDescriptions5[] = "Noise";
FLASHMEM static const char oscWaveformDescriptions6[] = "Sawstack x3 (stereo)";
FLASHMEM static const char oscWaveformDescriptions7[] = "Sawstack x7 (mono)";
FLASHMEM static const char oscWaveformDescriptions8[] = "Sawstack x7 (stereo)";

FLASHMEM static const char* const oscWaveformDescriptions[] = {
        oscWaveformDescriptions0,
        oscWaveformDescriptions1,
        oscWaveformDescriptions2,
        oscWaveformDescriptions3,
        oscWaveformDescriptions4,
        oscWaveformDescriptions5,
        oscWaveformDescriptions6,
        oscWaveformDescriptions7,
        oscWaveformDescriptions8
};

FLASHMEM static const char filterTypeDescriptions0[] = "Bypass";
FLASHMEM static const char filterTypeDescriptions1[] = "LPF 1P";
FLASHMEM static const char filterTypeDescriptions2[] = "LPF 2P";
FLASHMEM static const char filterTypeDescriptions3[] = "LPF 3P";
FLASHMEM static const char filterTypeDescriptions4[] = "LPF 4P";
FLASHMEM static const char filterTypeDescriptions5[] = "HPF 1P";
FLASHMEM static const char filterTypeDescriptions6[] = "HPF 2P";
FLASHMEM static const char filterTypeDescriptions7[] = "HPF 3P";
FLASHMEM static const char filterTypeDescriptions8[] = "HPF 4P";
FLASHMEM static const char filterTypeDescriptions9[] = "BPF 2P";
FLASHMEM static const char filterTypeDescriptions10[] = "BPF 4P";
FLASHMEM static const char filterTypeDescriptions11[] = "BRF 2P";
FLASHMEM static const char filterTypeDescriptions12[] = "BRF 4P";
FLASHMEM static const char filterTypeDescriptions13[] = "LP -> LP";
FLASHMEM static const char filterTypeDescriptions14[] = "LP -> BP";
FLASHMEM static const char filterTypeDescriptions15[] = "LP -> HP";
FLASHMEM static const char filterTypeDescriptions16[] = "LP // LP";
FLASHMEM static const char filterTypeDescriptions17[] = "LP // BP";
FLASHMEM static const char filterTypeDescriptions18[] = "LP // HP";
FLASHMEM static const char filterTypeDescriptions19[] = "BP // BP";
FLASHMEM static const char filterTypeDescriptions20[] = "BP // HP";
FLASHMEM static const char filterTypeDescriptions21[] = "HP // HP";

FLASHMEM static const char* const filterTypeDescriptions[] = {
        filterTypeDescriptions0,
        filterTypeDescriptions1,
        filterTypeDescriptions2,
        filterTypeDescriptions3,
        filterTypeDescriptions4,
        filterTypeDescriptions5,
        filterTypeDescriptions6,
        filterTypeDescriptions7,
        filterTypeDescriptions8,
        filterTypeDescriptions9,
        filterTypeDescriptions10,
        filterTypeDescriptions11,
        filterTypeDescriptions12,
        filterTypeDescriptions13,
        filterTypeDescriptions14,
        filterTypeDescriptions15,
        filterTypeDescriptions16,
        filterTypeDescriptions17,
        filterTypeDescriptions18,
        filterTypeDescriptions19,
        filterTypeDescriptions20,
        filterTypeDescriptions21
};

FLASHMEM static const char lfoWaveDescriptions0[] = "Triangle";
FLASHMEM static const char lfoWaveDescriptions1[] = "Square";
FLASHMEM static const char lfoWaveDescriptions2[] = "Saw Up";
FLASHMEM static const char lfoWaveDescriptions3[] = "Saw Down";
FLASHMEM static const char lfoWaveDescriptions4[] = "Sine";
FLASHMEM static const char lfoWaveDescriptions5[] = "Sin( x ) + Sin( 2x )";
FLASHMEM static const char lfoWaveDescriptions6[] = "Sin( x ) + Sin( 3x )";
FLASHMEM static const char lfoWaveDescriptions7[] = "Sin( x ) ^ 3";
FLASHMEM static const char lfoWaveDescriptions8[] = "Guitar";
FLASHMEM static const char lfoWaveDescriptions9[] = "S & H";

FLASHMEM static const char* const lfoWaveDescriptions[] = {
        lfoWaveDescriptions0,
        lfoWaveDescriptions1,
        lfoWaveDescriptions2,
        lfoWaveDescriptions3,
        lfoWaveDescriptions4,
        lfoWaveDescriptions5,
        lfoWaveDescriptions6,
        lfoWaveDescriptions7,
        lfoWaveDescriptions8,
        lfoWaveDescriptions9
};

FLASHMEM static const char lfoSyncDescriptions0[] = "Single, Free running";
FLASHMEM static const char lfoSyncDescriptions1[] = "Single, Key sync";
FLASHMEM static const char lfoSyncDescriptions2[] = "Multi, Free running";
FLASHMEM static const char lfoSyncDescriptions3[] = "Multi, Key sync";

FLASHMEM static const char* const lfoSyncDescriptions[] = {
        lfoSyncDescriptions0,
        lfoSyncDescriptions1,
        lfoSyncDescriptions2,
        lfoSyncDescriptions3
};

FLASHMEM static const char arpModeDesc0[] = "Off";
FLASHMEM static const char arpModeDesc1[] = "Up";
FLASHMEM static const char arpModeDesc2[] = "Down";
FLASHMEM static const char arpModeDesc3[] = "Up/Down";
FLASHMEM static const char arpModeDesc4[] = "As played";
FLASHMEM static const char arpModeDesc5[] = "Random";

FLASHMEM static const char* const arpModesDescriptions[] = {
    arpModeDesc0,
    arpModeDesc1,
    arpModeDesc2,
    arpModeDesc3,
    arpModeDesc4,
    arpModeDesc5
};

FLASHMEM static const char offOnDesc0[] = "OFF";
FLASHMEM static const char offOnDesc1[] = "ON";

FLASHMEM static const char* const offOn[] = {
    offOnDesc0,
    offOnDesc1
};

FLASHMEM static const char monoStereo0[] = "Mono";
FLASHMEM static const char monoStereo1[] = "Stereo";
FLASHMEM static const char monoStereo2[] = "Cross";

FLASHMEM static const char* const monoStereo[] = {
    monoStereo0,
    monoStereo1,
    monoStereo2
};

FLASHMEM static const char lfoModeDescriptions0[] = "Chorus Long";
FLASHMEM static const char lfoModeDescriptions1[] = "Chorus Short";
FLASHMEM static const char lfoModeDescriptions2[] = "Flanger Long";
FLASHMEM static const char lfoModeDescriptions3[] = "Flanger Short";

FLASHMEM static const char* const lfoModeDescriptions[] = {
    lfoModeDescriptions0,
    lfoModeDescriptions1,
    lfoModeDescriptions2,
    lfoModeDescriptions3
};

FLASHMEM static const char reverbModeDescriptions0[] = "Plate";
FLASHMEM static const char reverbModeDescriptions1[] = "Hall";

FLASHMEM static const char* const reverbModeDescriptions[] = {
    reverbModeDescriptions0,
    reverbModeDescriptions1
};

FLASHMEM static const char gainDbDescriptions0[] = "0 dB";
FLASHMEM static const char gainDbDescriptions1[] = "+6 dB";
FLASHMEM static const char gainDbDescriptions2[] = "+12 dB";
FLASHMEM static const char gainDbDescriptions3[] = "+18 dB";

FLASHMEM static const char* const gainDbDescriptions[] = {
    gainDbDescriptions0,
    gainDbDescriptions1,
    gainDbDescriptions2,
    gainDbDescriptions3
};

FLASHMEM static const char smearDescriptions0[] = "None";
FLASHMEM static const char smearDescriptions1[] = "16-bit";
FLASHMEM static const char smearDescriptions2[] = "15-bit";
FLASHMEM static const char smearDescriptions3[] = "14-bit";
FLASHMEM static const char smearDescriptions4[] = "13-bit";
FLASHMEM static const char smearDescriptions5[] = "12-bit";
FLASHMEM static const char smearDescriptions6[] = "11-bit";
FLASHMEM static const char smearDescriptions7[] = "10-bit";

FLASHMEM static const char* const smearDescriptions[] = {
    smearDescriptions0,
    smearDescriptions1,
    smearDescriptions2,
    smearDescriptions3,
    smearDescriptions4,
    smearDescriptions5,
    smearDescriptions6,
    smearDescriptions7
};

FLASHMEM static const char glideDescriptions0[] = "Off";
FLASHMEM static const char glideDescriptions1[] = "Always";
FLASHMEM static const char glideDescriptions2[] = "Only Legato Notes";

FLASHMEM static const char* const glideDescriptions[] = {
        glideDescriptions0,
        glideDescriptions1,
        glideDescriptions2
};

FLASHMEM static const char legatoDescriptions0[] = " Polyphonic ";
FLASHMEM static const char legatoDescriptions1[] = "Monophonic/Legato";

FLASHMEM static const char* const legatoDescriptions[] = {
        legatoDescriptions0,
        legatoDescriptions1
};

FLASHMEM static const char filterPostDescriptions0[] = "Full";
FLASHMEM static const char filterPostDescriptions1[] = "20 kHz";
FLASHMEM static const char filterPostDescriptions2[] = "18 kHz";
FLASHMEM static const char filterPostDescriptions3[] = "16 kHz";
FLASHMEM static const char filterPostDescriptions4[] = "14 kHz";
FLASHMEM static const char filterPostDescriptions5[] = "12 kHz";
FLASHMEM static const char filterPostDescriptions6[] = "10 kHz";
FLASHMEM static const char filterPostDescriptions7[] = "8 kHz";

FLASHMEM static const char* const filterPostDescriptions[] = {
    filterPostDescriptions0,
    filterPostDescriptions1,
    filterPostDescriptions2,
    filterPostDescriptions3,
    filterPostDescriptions4,
    filterPostDescriptions5,
    filterPostDescriptions6,
    filterPostDescriptions7
};

FLASHMEM static const char distortionTypeDescriptions0[] = "Hard clip";
FLASHMEM static const char distortionTypeDescriptions1[] = "Soft clip";
FLASHMEM static const char distortionTypeDescriptions2[] = "Tube 12AX";
FLASHMEM static const char distortionTypeDescriptions3[] = "Tube DSL";

FLASHMEM static const char* const distortionTypeDescriptions[] = {
    distortionTypeDescriptions0,
    distortionTypeDescriptions1,
    distortionTypeDescriptions2,
    distortionTypeDescriptions3
};

FLASHMEM static const char fxRoutingDescriptions0[] = "Chor/Phas/AM/Gate/Dly";
FLASHMEM static const char fxRoutingDescriptions1[] = "Gate/Dly/Chor/Phas/AM";
FLASHMEM static const char fxRoutingDescriptions2[] = "Bypass effects";

FLASHMEM static const char* const fxRoutingDescriptions[] = {
    fxRoutingDescriptions0,
    fxRoutingDescriptions1,
    fxRoutingDescriptions2
};

FLASHMEM static const char gateCurveDescriptions0[] = "S-Shape 1";
FLASHMEM static const char gateCurveDescriptions1[] = "S-Shape 2";

FLASHMEM static const char* const gateCurveDescriptions[] = {
    gateCurveDescriptions0,
    gateCurveDescriptions1
};

FLASHMEM static const char lrModeDescriptions0[] = "Standard";
FLASHMEM static const char lrModeDescriptions1[] = "LR Mode";

FLASHMEM static const char* const lrModeDescriptions[] = {
    lrModeDescriptions0,
    lrModeDescriptions1
};

FLASHMEM static const char phaseDescriptions0[] = "0 deg";
FLASHMEM static const char phaseDescriptions1[] = "90 deg";
FLASHMEM static const char phaseDescriptions2[] = "180 deg";
FLASHMEM static const char phaseDescriptions3[] = "270 deg";

FLASHMEM static const char* const phaseDescriptions[] = {
    phaseDescriptions0,
    phaseDescriptions1,
    phaseDescriptions2,
    phaseDescriptions3
};


#endif //XVA1USERINTERFACE_SECTIONFACTORY_H
