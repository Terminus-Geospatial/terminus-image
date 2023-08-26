/**
 * @file    statistics.hpp
 * @author  Marvin Smith
 * @date    8/21/2023
*/
#pragma once

namespace tmns::image::ops {

/**
 * Locate the minimum value of of all channels stored in all planes of the 
 * image
*/
template <class ImageT>
typename Pixel_Channel_Type<typename ImageT::pixel_type>::type
  min_channel_value( const Image_Base<ImageT>& view )
{
    typedef typename PixelChannelType<typename ViewT::pixel_type>::type accum_type;
    ChannelAccumulator<MinMaxAccumulator<accum_type> > accumulator;
    for_each_pixel( view, accumulator );
    return accumulator.minimum();
  }

  /// Compute the maximum value stored in all of the channels of all
  /// of the planes of the images.
  template <class ViewT>
  typename PixelChannelType<typename ViewT::pixel_type>::type
  max_channel_value( const ImageViewBase<ViewT>& view ) {
    typedef typename PixelChannelType<typename ViewT::pixel_type>::type accum_type;
    ChannelAccumulator<MinMaxAccumulator<accum_type> > accumulator;
    for_each_pixel( view, accumulator );
    return accumulator.maximum();
  }

  /// Simultaneously compute the min and max value in all of the
  /// channels of all of the planes of the image.
  template <class ViewT>
  void min_max_channel_values( const ImageViewBase<ViewT> &view,
                               typename PixelChannelType<typename ViewT::pixel_type>::type &min,
                               typename PixelChannelType<typename ViewT::pixel_type>::type &max )
  {
    typedef typename PixelChannelType<typename ViewT::pixel_type>::type accum_type;
    ChannelAccumulator<MinMaxAccumulator<accum_type> > accumulator;
    for_each_pixel( view, accumulator );
    min = accumulator.minimum();
    max = accumulator.maximum();
  }

  /// Compute the sum of all the channels of all the valid pixels of the image.
  template <class ViewT>
  typename AccumulatorType<typename PixelChannelType<typename ViewT::pixel_type>::type>::type
  sum_of_channel_values( const ImageViewBase<ViewT>& view ) {
    typedef typename AccumulatorType<typename PixelChannelType<typename ViewT::pixel_type>::type>::type accum_type;
    ChannelAccumulator<Accumulator<accum_type> > accumulator;
    for_each_pixel( view, accumulator );
    return accumulator.value();
  }

  /// Computes the mean of the values of the channels of all of the
  /// valid (non-masked) pixels of an image (including alpha but
  /// excluding mask channels).
  template <class ViewT>
  double mean_channel_value( const ImageViewBase<ViewT> &view ) {
    typedef typename PixelChannelType<typename ViewT::pixel_type>::type accum_type;
    ChannelAccumulator<MeanAccumulator<accum_type> > accumulator;
    for_each_pixel( view, accumulator );
    return accumulator.value();
  }

  /// Computes the standard deviation of the values of all the
  /// channels of all of the planes of an image.  For images that have
  /// an alpha channel, this function computes the weighted standard
  /// deviation, using the alpha channel as a weight and assuming
  /// pre-multiplied pixel values.  This function throws an
  /// ArgumentErr() exception if the image has zero size or is
  /// completely transparent.
  ///
  /// Note: This function computes the total stanadard deviation, not
  /// the sample standard deviation as was computed by previous
  /// versions.  If you need the sample standard deviation, just
  /// multiply the result by sqrt(num_samples/(num_samples-1)), where
  /// num_samples=channels*cols*rows*planes.  Note that the concept
  /// of sample standard deviation is not particularly meaningful for
  /// images with alpha channels.
  ///
  template <class ViewT>
  double stddev_channel_value( const ImageViewBase<ViewT> &view ) {
    typedef typename PixelChannelType<typename ViewT::pixel_type>::type channel_type;
    ChannelAccumulator<StdDevAccumulator<channel_type> > accumulator;
    for_each_pixel( view, accumulator );
    return accumulator.value();
  }

  /// Computes the median channel value of an image.  Only non-alpha
  /// channels of valid (e.g.  non-transparent) pixels are considered.
  /// This function computes the median by sorting all the channel
  /// values in the image, which is time- and memory-intensive, so
  /// this operation is not recommended for large images.
  template <class ViewT>
  typename PixelChannelType<typename ViewT::pixel_type>::type
  median_channel_value( const ImageViewBase<ViewT> &view ) {
    typedef typename PixelChannelType<typename ViewT::pixel_type>::type accum_type;
    ChannelAccumulator<MedianAccumulator<accum_type> > accumulator;
    for_each_pixel( view, accumulator );
    return accumulator.value();
  }

} // End of tmns::image::ops namespace