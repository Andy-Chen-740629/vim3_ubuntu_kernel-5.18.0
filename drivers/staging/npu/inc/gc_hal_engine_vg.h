/****************************************************************************
*
*    Copyright (c) 2005 - 2021 by Vivante Corp.  All rights reserved.
*
*    The material in this file is confidential and contains trade secrets
*    of Vivante Corporation. This is proprietary information owned by
*    Vivante Corporation. No part of this work may be disclosed,
*    reproduced, copied, transmitted, or used in any way for any purpose,
*    without the express written permission of Vivante Corporation.
*
*****************************************************************************/


#ifndef __gc_hal_engine_vg_h_
#define __gc_hal_engine_vg_h_

#ifdef __cplusplus
extern "C" {
#endif

#include "gc_hal_types.h"

/******************************************************************************\
******************************** VG Structures *******************************
\******************************************************************************/

/**
**  @ingroup    gcoVG
**
**  @brief      Definition of the color ramp used by the gradient paints.
**
**  The gcsCOLOR_RAMP structure defines the layout of one single color inside
**  a color ramp which is used by gradient paints.
*/
typedef struct _gcsCOLOR_RAMP
{
    /** Value for the color stop. */
    gctFLOAT        stop;

    /** Red color channel value for the color stop. */
    gctFLOAT        red;

    /** Green color channel value for the color stop. */
    gctFLOAT        green;

    /** Blue color channel value for the color stop. */
    gctFLOAT        blue;

    /** Alpha color channel value for the color stop. */
    gctFLOAT        alpha;
}
gcsCOLOR_RAMP, * gcsCOLOR_RAMP_PTR;

/**
**  @ingroup    gcoVG
**
**  @brief      Definition of the color ramp used by the gradient paints in fixed form.
**
**  The gcsCOLOR_RAMP structure defines the layout of one single color inside
**  a color ramp which is used by gradient paints.
*/
typedef struct _gcsFIXED_COLOR_RAMP
{
    /** Value for the color stop. */
    gctFIXED_POINT      stop;

    /** Red color channel value for the color stop. */
    gctFIXED_POINT      red;

    /** Green color channel value for the color stop. */
    gctFIXED_POINT      green;

    /** Blue color channel value for the color stop. */
    gctFIXED_POINT      blue;

    /** Alpha color channel value for the color stop. */
    gctFIXED_POINT      alpha;
}
gcsFIXED_COLOR_RAMP, * gcsFIXED_COLOR_RAMP_PTR;


/**
**  @ingroup gcoVG
**
**  @brief  Rectangle structure used by the gcoVG object.
**
**  This structure defines the layout of a rectangle.  Make sure width and
**  height are larger than 0.
*/
typedef struct _gcsVG_RECT * gcsVG_RECT_PTR;
typedef struct _gcsVG_RECT
{
    /** Left location of the rectangle. */
    gctINT      x;

    /** Top location of the rectangle. */
    gctINT      y;

    /** Width of the rectangle. */
    gctINT      width;

    /** Height of the rectangle. */
    gctINT      height;
}
gcsVG_RECT;

/**
**  @ingroup    gcoVG
**
**  @brief      Path command buffer attribute structure.
**
**  The gcsPATH_BUFFER_INFO structure contains the specifics about
**  the layout of the path data command buffer.
*/
typedef struct _gcsPATH_BUFFER_INFO * gcsPATH_BUFFER_INFO_PTR;
typedef struct _gcsPATH_BUFFER_INFO
{
    gctUINT     reservedForHead;
    gctUINT     reservedForTail;
}
gcsPATH_BUFFER_INFO;

/**
**  @ingroup    gcoVG
**
**  @brief      Definition of the path data container structure.
**
**  The gcsPATH structure defines the layout of the path data container.
*/
typedef struct _gcsPATH_DATA * gcsPATH_DATA_PTR;
typedef struct _gcsPATH_DATA
{
    /* Data container in command buffer format. */
    gcsCMDBUFFER    data;

    /* Path data type. */
    gcePATHTYPE     dataType;
}
gcsPATH_DATA;


/******************************************************************************\
********************************* gcoHAL Object ********************************
\******************************************************************************/

/* Query path data storage attributes. */
gceSTATUS
gcoHAL_QueryPathStorage(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    OUT gcsPATH_BUFFER_INFO_PTR Information
    );

/* Associate a completion signal with the command buffer. */
gceSTATUS
gcoHAL_AssociateCompletion(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcsPATH_DATA_PTR PathData
    );

/* Release the current command buffer completion signal. */
gceSTATUS
gcoHAL_DeassociateCompletion(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcsPATH_DATA_PTR PathData
    );

/* Verify whether the command buffer is still in use. */
gceSTATUS
gcoHAL_CheckCompletion(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcsPATH_DATA_PTR PathData
    );

/* Wait until the command buffer is no longer in use. */
gceSTATUS
gcoHAL_WaitCompletion(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcsPATH_DATA_PTR PathData
    );

/* Flush the pixel cache. */
gceSTATUS
gcoHAL_Flush(
#if gcdGC355_PROFILER
    IN gcoHAL Hal,
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth
#else
    IN gcoHAL Hal
#endif
    );

/* Split a harwdare address into pool and offset. */
gceSTATUS
gcoHAL_SplitAddress(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctUINT32 Address,
    OUT gcePOOL * Pool,
    OUT gctUINT32 * Offset
    );

/* Combine pool and offset into a harwdare address. */
gceSTATUS
gcoHAL_CombineAddress(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcePOOL Pool,
    IN gctUINT32 Offset,
    OUT gctUINT32 * Address
    );

/* Schedule to free linear video memory allocated. */
gceSTATUS
gcoHAL_ScheduleVideoMemory(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctUINT32 Node
    );

/* Free linear video memory allocated with gcoHAL_AllocateLinearVideoMemory. */
gceSTATUS
gcoHAL_FreeVideoMemory(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctUINT32 Node,
    IN gctBOOL asynchroneous
    );

/* Query command buffer attributes. */
gceSTATUS
gcoHAL_QueryCommandBuffer(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    OUT gcsCOMMAND_BUFFER_INFO_PTR Information
    );
/* Allocate and lock linear video memory. */
gceSTATUS
gcoHAL_AllocateLinearVideoMemory(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctUINT Size,
    IN gctUINT Alignment,
    IN gcePOOL Pool,
    OUT gctUINT32 * Node,
    OUT gctUINT32 * Address,
    OUT gctPOINTER * Memory
    );

/* Align the specified size accordingly to the hardware requirements. */
gceSTATUS
gcoHAL_GetAlignedSurfaceSize(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gceSURF_TYPE Type,
    IN OUT gctUINT32_PTR Width,
    IN OUT gctUINT32_PTR Height
    );

gceSTATUS
gcoHAL_ReserveTask(
    IN gcoHAL Hal,
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gceBLOCK Block,
    IN gctUINT TaskCount,
    IN gctUINT32 Bytes,
    OUT gctPOINTER * Memory
    );
/******************************************************************************\
********************************** gcoVG Object ********************************
\******************************************************************************/

/** @defgroup gcoVG gcoVG
**
**  The gcoVG object abstracts the VG hardware pipe.
*/
#if gcdGC355_PROFILER
void
gcoVG_ProfilerEnableDisable(
    IN gcoVG Vg,
    IN gctUINT enableGetAPITimes,
    IN gctFILE apiTimeFile
    );

void
gcoVG_ProfilerTreeDepth(
    IN gcoVG Vg,
    IN gctUINT TreeDepth
    );

void
gcoVG_ProfilerSetStates(
    IN gcoVG Vg,
    IN gctUINT treeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth
    );
#endif

gctBOOL
gcoVG_IsMaskSupported(
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gceSURF_FORMAT Format
    );

gctBOOL
gcoVG_IsTargetSupported(
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gceSURF_FORMAT Format
    );

gctBOOL
gcoVG_IsImageSupported(
#if gcdGC355_PROFILER
    IN gcoVG Vg,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gceSURF_FORMAT Format
    );

gctUINT8 gcoVG_PackColorComponent(
#if gcdGC355_PROFILER
    gcoVG Vg,
    gctUINT TreeDepth,
    gctUINT saveLayerTreeDepth,
    gctUINT varTreeDepth,
#endif
    gctFLOAT Value
    );

gceSTATUS
gcoVG_Construct(
    IN gcoHAL Hal,
    OUT gcoVG * Vg
    );

gceSTATUS
gcoVG_Destroy(
    IN gcoVG Vg
#if gcdGC355_PROFILER
,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth
#endif
    );

void
gcoVG_SetTesselationSize(
    IN gcoVG Vg,
    IN gctUINT Width,
    IN gctUINT Height
    );

gceSTATUS
gcoVG_SetTarget(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcoSURF Target,
    IN gceORIENTATION orientation
    );

gceSTATUS
gcoVG_UnsetTarget(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcoSURF Surface
    );

gceSTATUS
gcoVG_SetUserToSurface(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctFLOAT UserToSurface[9]
    );

gceSTATUS
gcoVG_SetSurfaceToImage(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctFLOAT SurfaceToImage[9]
    );

gceSTATUS
gcoVG_EnableMask(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctBOOL Enable
    );

gceSTATUS
gcoVG_SetMask(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcoSURF Mask
    );

gceSTATUS
gcoVG_UnsetMask(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcoSURF Surface
    );

gceSTATUS
gcoVG_FlushMask(
    IN gcoVG Vg
#if gcdGC355_PROFILER
,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth
#endif
    );

gceSTATUS
gcoVG_EnableScissor(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctBOOL Enable
    );

gceSTATUS
gcoVG_SetScissor(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctSIZE_T RectangleCount,
    IN gcsVG_RECT_PTR Rectangles
    );

gceSTATUS
gcoVG_EnableColorTransform(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctBOOL Enable
    );

gceSTATUS
gcoVG_SetColorTransform(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctFLOAT ColorTransform[8]
    );

gceSTATUS
gcoVG_SetTileFillColor(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctFLOAT Red,
    IN gctFLOAT Green,
    IN gctFLOAT Blue,
    IN gctFLOAT Alpha
    );

gceSTATUS
gcoVG_SetSolidPaint(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctUINT8 Red,
    IN gctUINT8 Green,
    IN gctUINT8 Blue,
    IN gctUINT8 Alpha
    );

gceSTATUS
gcoVG_SetLinearPaint(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctFLOAT Constant,
    IN gctFLOAT StepX,
    IN gctFLOAT StepY
    );

gceSTATUS
gcoVG_SetRadialPaint(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctFLOAT LinConstant,
    IN gctFLOAT LinStepX,
    IN gctFLOAT LinStepY,
    IN gctFLOAT RadConstant,
    IN gctFLOAT RadStepX,
    IN gctFLOAT RadStepY,
    IN gctFLOAT RadStepXX,
    IN gctFLOAT RadStepYY,
    IN gctFLOAT RadStepXY
    );

gceSTATUS
gcoVG_SetPatternPaint(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctFLOAT UConstant,
    IN gctFLOAT UStepX,
    IN gctFLOAT UStepY,
    IN gctFLOAT VConstant,
    IN gctFLOAT VStepX,
    IN gctFLOAT VStepY,
    IN gctBOOL Linear
    );

gceSTATUS
gcoVG_SetColorRamp(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcoSURF ColorRamp,
    IN gceTILE_MODE ColorRampSpreadMode
    );

gceSTATUS
gcoVG_SetPattern(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctINT32 width,
    IN gctINT32 height,
    IN gcoSURF Pattern,
    IN gceTILE_MODE TileMode,
    IN gceIMAGE_FILTER Filter
    );

gceSTATUS
gcoVG_SetImageMode(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gceVG_IMAGE Mode
    );

gceSTATUS
gcoVG_SetBlendMode(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gceVG_BLEND Mode
    );

gceSTATUS
gcoVG_SetRenderingQuality(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gceRENDER_QUALITY Quality
    );

gceSTATUS
gcoVG_SetFillRule(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gceFILL_RULE FillRule
    );

gceSTATUS
gcoVG_FinalizePath(
    IN gcoVG Vg,
    IN gcsPATH_DATA_PTR PathData
    );

gceSTATUS
gcoVG_Clear(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctINT X,
    IN gctINT Y,
    IN gctINT Width,
    IN gctINT Height
    );

gceSTATUS
gcoVG_DrawPath(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcsPATH_DATA_PTR PathData,
    IN gctFLOAT Scale,
    IN gctFLOAT Bias,
#if gcdMOVG
    IN gctUINT32 Width,
    IN gctUINT32 Height,
    IN gctFLOAT *Bounds,
#endif
    IN gctBOOL SoftwareTesselation
    );

gceSTATUS
gcoVG_DrawImage(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gceORIENTATION orientation,
    IN gcoSURF Source,
    IN gcsPOINT_PTR SourceOrigin,
    IN gcsPOINT_PTR TargetOrigin,
    IN gcsSIZE_PTR SourceSize,
    IN gctINT SourceX,
    IN gctINT SourceY,
    IN gctINT TargetX,
    IN gctINT TargetY,
    IN gctINT Width,
    IN gctINT Height,
    IN gctBOOL Mask,
    IN gctBOOL isDrawImage
    );

gceSTATUS
gcoVG_TesselateImage(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcoSURF Image,
    IN gcsVG_RECT_PTR Rectangle,
    IN gceIMAGE_FILTER Filter,
    IN gctBOOL Mask,
#if gcdMOVG
    IN gctBOOL SoftwareTesselation,
    IN gceVG_BLEND BlendMode,
    IN gctINT Width,
    IN gctINT Height
#else
    IN gctBOOL SoftwareTesselation
#endif
    );

gceSTATUS
gcoVG_DrawSurfaceToImage(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcoSURF Image,
    IN const gcsVG_RECT_PTR SrcRectangle,
    IN const gctFLOAT  DstBounds[4],
    IN const gctFLOAT DstPoints[8],
    IN const gctFLOAT ImgMatrix[9],
    IN const gctFLOAT RectMatrix[9],
    IN gceIMAGE_FILTER Filter,
    IN gctBOOL Mask,
    IN gctBOOL FirstTime
#if gcdMOVG
,
    IN gctINT   TSWidth,
    IN gctINT   TSHeight
#endif
    );

gceSTATUS
gcoVG_DrawSurfaceToImageMasked(
    IN gcoVG Vg,
    IN gcoSURF Image,
    IN gcsVG_RECT_PTR SrcRect,
    IN gctINT  X,
    IN gctINT  Y,
    IN gctINT  Width,
    IN gctINT  Height,
    IN const gctFLOAT Matrix[9]
    );

gceSTATUS
gcoVG_Blit(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcoSURF Source,
    IN gcoSURF Target,
    IN gcsVG_RECT_PTR SrcRect,
    IN gcsVG_RECT_PTR TrgRect,
    IN gceIMAGE_FILTER Filter,
    IN gceVG_BLEND Mode
    );

gceSTATUS
gcoVG_ColorMatrix(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcoSURF Source,
    IN gcoSURF Target,
    IN const gctFLOAT * Matrix,
    IN gceCHANNEL ColorChannels,
    IN gctBOOL FilterLinear,
    IN gctBOOL FilterPremultiplied,
    IN gcsPOINT_PTR SourceOrigin,
    IN gcsPOINT_PTR TargetOrigin,
    IN gctINT Width,
    IN gctINT Height
    );

gceSTATUS
gcoVG_SeparableConvolve(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcoSURF Source,
    IN gcoSURF Target,
    IN gctINT KernelWidth,
    IN gctINT KernelHeight,
    IN gctINT ShiftX,
    IN gctINT ShiftY,
    IN const gctINT16 * KernelX,
    IN const gctINT16 * KernelY,
    IN gctFLOAT Scale,
    IN gctFLOAT Bias,
    IN gceTILE_MODE TilingMode,
    IN gctFLOAT_PTR FillColor,
    IN gceCHANNEL ColorChannels,
    IN gctBOOL FilterLinear,
    IN gctBOOL FilterPremultiplied,
    IN gcsPOINT_PTR SourceOrigin,
    IN gcsPOINT_PTR TargetOrigin,
    IN gcsSIZE_PTR SourceSize,
    IN gctINT Width,
    IN gctINT Height
    );

gceSTATUS
gcoVG_GaussianBlur(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gcoSURF Source,
    IN gcoSURF Target,
    IN gctFLOAT StdDeviationX,
    IN gctFLOAT StdDeviationY,
    IN gceTILE_MODE TilingMode,
    IN gctFLOAT_PTR FillColor,
    IN gceCHANNEL ColorChannels,
    IN gctBOOL FilterLinear,
    IN gctBOOL FilterPremultiplied,
    IN gcsPOINT_PTR SourceOrigin,
    IN gcsPOINT_PTR TargetOrigin,
    IN gcsSIZE_PTR SourceSize,
    IN gctINT Width,
    IN gctINT Height
    );

gceSTATUS
gcoVG_EnableDither(
    IN gcoVG Vg,
#if gcdGC355_PROFILER
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctBOOL Enable
    );

/* Color Key States. */
gceSTATUS
gcoVG_SetColorKey(
    IN gcoVG        Vg,
#if gcdGC355_PROFILER
    IN gcsPROFILERFUNCNODE *DList,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctUINT32*    Values,
    IN gctBOOL *    Enables
);

/* Index Color States. */
gceSTATUS
gcoVG_SetColorIndexTable(
    IN gcoVG        Vg,
#if gcdGC355_PROFILER
    IN gcsPROFILERFUNCNODE *DList,
    IN gctUINT TreeDepth,
    IN gctUINT saveLayerTreeDepth,
    IN gctUINT varTreeDepth,
#endif
    IN gctUINT32*    Values,
    IN gctINT32      Count
);

gceSTATUS
gcoVG_SetYUV2RGBStdCust(
    IN gcoVG            Vg,
    IN gctBOOL          YUV2RGBStdCust
    );

gceSTATUS
gcoVG_SetYUV2RGB(
    IN gcoVG            Vg,
    IN gctFLOAT         *coef,
    IN gctFLOAT         *offset,
    IN gctBOOL          *cfg
);

gceSTATUS
gcoVG_SetRGB2YUVParameters(
    IN gcoVG            Vg,
    IN gctFLOAT         *coef,
    IN gctFLOAT         *offset,
    IN gctBOOL          *cfg
);

/* VG RS feature support: YUV format conversion. */
gceSTATUS
gcoVG_Resolve(
    IN gcoVG        Vg,
    IN gcoSURF      Source,
    IN gcoSURF      Target,
    IN gctINT       SX,
    IN gctINT       SY,
    IN gctINT       DX,
    IN gctINT       DY,
    IN gctINT       Width,
    IN gctINT       Height,
    IN gctINT       Src_uv,
    IN gctINT       Src_standard,
    IN gctINT       Dst_uv,
    IN gctINT       Dst_standard,
    IN gctINT       Dst_alpha,
    IN gctBOOL      Dst_standard_cust
);
#ifdef __cplusplus
}
#endif

#endif  /* __gc_hal_vg_h_ */


