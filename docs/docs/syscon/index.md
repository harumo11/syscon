---
title: syscon
description: 
generator: doxide
---


# syscon



## Functions

| Name | Description |
| ---- | ----------- |
| [T2fc](#T2fc) | convert from time constant $T$ [s] to cut-off frequency $f_c$ [Hz]. |
| [T2wc](#T2wc) | convert from time constant $T$ [s] to cut-off frequency $w_c$ [rad/s]. |
| [fc2T](#fc2T) | convert from cut-off frequency $f_c$ [Hz] to time constant $T$ [s]. |
| [fc2wc](#fc2wc) | convert from cut-off frequency $f_c$ [Hz] to cut-off frequency $w_c$ [rad/s]. |
| [wc2T](#wc2T) | convert from cut-off frequency $w_c$ [rad/s] to time constant $T$ [s]. |

## Function Details

### T2fc<a name="T2fc"></a>
!!! function "double T2fc(auto const T)"

    
    
    convert from time constant $T$ [s] to cut-off frequency $f_c$ [Hz].
    
    $$
    f_c = \frac{1}{2\pi T}
    $$
    
    :material-location-enter: **Parameter** `T`
    :    Time constant [s]
    
    :material-keyboard-return: **Return**
    :    cut-off frequency [Hz]
    
    

### T2wc<a name="T2wc"></a>
!!! function "double T2wc(auto const T)"

    
    
    convert from time constant $T$ [s] to cut-off frequency $w_c$ [rad/s].
    
    $$
    w_c = \frac{1}{T}
    $$
    
    :material-location-enter: **Parameter** `T`
    :    Time constant [s]
    
    :material-keyboard-return: **Return**
    :    cut-off frequency $w_c$ [rad/s]
    
    

### fc2T<a name="fc2T"></a>
!!! function "double fc2T(auto const fc)"

    
    
    convert from cut-off frequency $f_c$ [Hz] to time constant $T$ [s].
    
    $$
    T = \frac{1}{2\pi f_c}
    $$
    
    :material-location-enter: **Parameter** `fc`
    :    cut-off frequency [Hz]
    
    :material-keyboard-return: **Return**
    :    Time constant T [s]
    
    

### fc2wc<a name="fc2wc"></a>
!!! function "double fc2wc(auto const fc)"

    
    
    convert from cut-off frequency $f_c$ [Hz] to cut-off frequency $w_c$ [rad/s].
    
    $$
    w_c = 2\pi f_c
    $$
    
    :material-location-enter: **Parameter** `fc`
    :    cut-off frequency [Hz]
    
    :material-keyboard-return: **Return**
    :    cut-off frequency $w_c$ [rad/s]
    
    

### wc2T<a name="wc2T"></a>
!!! function "double wc2T(auto const wc)"

    
    
    convert from cut-off frequency $w_c$ [rad/s] to time constant $T$ [s].
    
    $$
    T = \frac{1}{w_c}
    $$
    
    :material-location-enter: **Parameter** `wc`
    :    cuf-off frequency [rad/s]
    
    :material-keyboard-return: **Return**
    :    Time constant [s]
    
    

