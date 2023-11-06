/**
 * @file    Collection_Resource_File.hpp
 * @author  Marvin Smith
 * @date    8/26/2023
 */
#pragma once

// Terminus Libraries
#include <terminus/core/error/ErrorCode.hpp>

// Terminus Image Libraries
#include "../io/read_image_disk.hpp"
#include "file/File_Collection_Utilities.hpp"
#include "Collection_Resource_Base.hpp"

// C++ Libraries
#include <filesystem>
#include <memory>
#include <vector>

namespace tmns::image::cx {

/**
 * @class Collection_Resource_File
 */
template <typename PixelT>
class Collection_Resource_File : public Collection_Resource_Base<Collection_Resource_File<PixelT>>
{
    public:

        typedef std::unique_ptr<Collection_Resource_File> ptr_t;

        /// Iterator Type
        using iter_type  = typename std::vector<Image_Disk<PixelT>>::iterator;
        using citer_type = typename std::vector<Image_Disk<PixelT>>::const_iterator;

        /**
         * Constructor
         * @param images List of partially loaded images.
        */
        Collection_Resource_File( std::vector<Image_Disk<PixelT>> images )
          : m_images( std::move( images ) )
        {
        }

        static ImageResult<Collection_Resource_File::ptr_t> load_image_list( const std::filesystem::path image_file )
        {
            // Parse the INI file
            std::vector<std::filesystem::path> image_list;
            auto init_result = file::parse_toml_collection_file( image_file,
                                                                 image_list );

            // Create list of disk-images
            auto disk_driver_manager = io::Disk_Driver_Manager::create_read_defaults();
            std::vector<Image_Disk<PixelT>> disk_images;
            for( const auto& image_path : image_list )
            {
                tmns::log::debug( "Loading image: ", image_path.native() );
                auto res = io::read_image_disk<PixelT>( image_path,
                                                        disk_driver_manager );
                
                // If the operation fails, log it, but still move on
                if( res.has_error() )
                {
                    tmns::log::error( "Unable to load image: ", image_path,
                                      ". Skipping image.  What: ", res.error().message() );
                    continue;
                }

                tmns::log::trace( "Adding to list" );
                disk_images.push_back( std::move( res.value() ) );
            }

            // Create output resource
            auto output = std::make_unique<Collection_Resource_File>( disk_images );

            return output;
        }

        size_t size() const
        {
            return m_images.size();
        }

        iter_type begin()
        {
            return m_images.begin(); 
        }

        citer_type cbegin() const
        {
            return m_images.cbegin(); 
        }

        iter_type end()
        {
            return m_images.end();
        }

        citer_type cend() const
        {
            return m_images.cend();
        }

    private:

        /// Global Camera Model


        /// List of loaded images
        std::vector<Image_Disk<PixelT>> m_images;

}; // End of Collection_Resource_File class

} // End of tmns::image::cx namespace