.globl _nmppsThreshold_16s
.globl _nmppsThreshold_32s
.globl _nmppsThreshold_32f
.globl _nmppsThreshold_64f

.global threshold_lt_16s
.global threshold_gt_16s

.global threshold_gt_32f
.global threshold_lt_32f

.global threshold_gt_64f
.global threshold_lt_64f

.text

_nmppsThreshold_16s:
_nmppsThreshold_32s:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  ar0 = [--ar5]; //psrc
  ar1 = [--ar5]; //pdst
  gr0 = [--ar5]; //len
  gr1 = [--ar5]; //level
  gr2 = [--ar5];

  gr5 = 0;
  gr2 - gr5;
  if =0 goto call_threshold_lt_16s;

  gr5 = 4;
  gr2 - gr5;
  if =0 goto call_threshold_gt_16s;

  gr7 = -5;

  goto exit_threshold_16s;

call_threshold_lt_16s:
  call threshold_lt_16s;

  goto exit_threshold_16s;

call_threshold_gt_16s:
  call threshold_gt_16s;

exit_threshold_16s:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;


_nmppsThreshold_32f:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;

  ar0 = [--ar5]; //psrc
  ar1 = [--ar5]; //pdst
  gr0 = [--ar5]; //len
  gr1 = [--ar5]; //level
  gr2 = [--ar5];

  gr5 = 0;
  gr2 - gr5;
  if =0 goto call_threshold_lt_32f;

  gr5 = 4;
  gr2 - gr5;
  if =0 goto call_threshold_gt_32f;

  gr7 = -5;

  goto exit_threshold_32f;

call_threshold_lt_32f:
  call threshold_lt_32f;

  goto exit_threshold_32f;

call_threshold_gt_32f:
  call threshold_gt_32f;

exit_threshold_32f:
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;


_nmppsThreshold_64f:
  ar5 = ar7 - 2;
  push ar0, gr0;
  push ar1, gr1;
  push ar2, gr2;
  push ar3, gr3;

  ar0 = [--ar5]; //psrc
  ar1 = [--ar5]; //pdst
  gr0 = [--ar5]; //len
  ar3,gr3 = [--ar5]; //level
  ar5 = ar5 - 1;
  gr2 = [--ar5];

  gr5 = 0;
  gr2 - gr5;
  if =0 goto call_threshold_lt_64f;

  gr5 = 4;
  gr2 - gr5;
  if =0 goto call_threshold_gt_64f;

  gr7 = -5;

  goto exit_threshold_64f;

call_threshold_lt_64f:
  call threshold_lt_64f;

  goto exit_threshold_64f;

call_threshold_gt_64f:
  call threshold_gt_64f;

exit_threshold_64f:
  pop ar3, gr3;
  pop ar2, gr2;
  pop ar1, gr1;
  pop ar0, gr0;

  return;
