/*
-----------------------------------------------------------------------------
This source file is part of OGRE-Next
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "OgreStableHeaders.h"

#include "OgreMesh2Serializer.h"

#include "OgreException.h"
#include "OgreLogManager.h"
#include "OgreMesh2.h"

#include <fstream>

namespace Ogre
{
    const unsigned short HEADER_CHUNK_ID = 0x1000;
    //---------------------------------------------------------------------
    MeshSerializer::MeshSerializer( VaoManager *vaoManager ) : mListener( 0 )
    {
        // Init implementations
        // String identifiers have not always been 100% unified with OGRE version

        // Note MUST be added in reverse order so latest is first in the list

        mVersionData.push_back( OGRE_NEW MeshVersionData( MESH_VERSION_2_1, "[MeshSerializer_v2.1 R2]",
                                                          OGRE_NEW MeshSerializerImpl( vaoManager ) ) );

        // These formats will be removed on release
        mVersionData.push_back(
            OGRE_NEW MeshVersionData( MESH_VERSION_LEGACY, "[MeshSerializer_v2.1 R1]",
                                      OGRE_NEW MeshSerializerImpl_v2_1_R1( vaoManager ) ) );

        mVersionData.push_back(
            OGRE_NEW MeshVersionData( MESH_VERSION_LEGACY, "[MeshSerializer_v2.1]",
                                      OGRE_NEW MeshSerializerImpl_v2_1_R0( vaoManager ) ) );
    }
    //---------------------------------------------------------------------
    MeshSerializer::~MeshSerializer()
    {
        // delete map
        for( MeshVersionDataList::iterator i = mVersionData.begin(); i != mVersionData.end(); ++i )
        {
            OGRE_DELETE *i;
        }
        mVersionData.clear();
    }
    //---------------------------------------------------------------------
    void MeshSerializer::exportMesh( const Mesh *pMesh, const String &filename, Endian endianMode )
    {
        std::fstream *f = OGRE_NEW_T( std::fstream, MEMCATEGORY_GENERAL )();
        f->open( filename.c_str(), std::ios::binary | std::ios::out );
        DataStreamPtr stream( OGRE_NEW FileStreamDataStream( f ) );

        exportMesh( pMesh, stream, endianMode );

        stream->close();
    }
    //---------------------------------------------------------------------
    void MeshSerializer::exportMesh( const Mesh *pMesh, const String &filename, MeshVersion version,
                                     Endian endianMode )
    {
        if( version == MESH_VERSION_LEGACY )
        {
            OGRE_EXCEPT( Exception::ERR_INVALIDPARAMS,
                         "You may not supply a legacy version number for writing meshes.",
                         "MeshSerializer::exportMesh" );
        }

        std::fstream *f = OGRE_NEW_T( std::fstream, MEMCATEGORY_GENERAL )();
        f->open( filename.c_str(), std::ios::binary | std::ios::out );
        DataStreamPtr stream( OGRE_NEW FileStreamDataStream( f ) );

        exportMesh( pMesh, stream, version, endianMode );

        stream->close();
    }
    //---------------------------------------------------------------------
    void MeshSerializer::exportMesh( const Mesh *pMesh, DataStreamPtr stream, Endian endianMode )
    {
        exportMesh( pMesh, stream, MESH_VERSION_LATEST, endianMode );
    }
    //---------------------------------------------------------------------
    void MeshSerializer::exportMesh( const Mesh *pMesh, DataStreamPtr stream, MeshVersion version,
                                     Endian endianMode )
    {
        MeshSerializerImpl *impl = 0;
        if( version == MESH_VERSION_LATEST )
            impl = mVersionData[0]->impl;
        else
        {
            for( MeshVersionDataList::iterator i = mVersionData.begin(); i != mVersionData.end(); ++i )
            {
                if( version == ( *i )->version )
                {
                    impl = ( *i )->impl;
                    break;
                }
            }
        }

        if( !impl )
        {
            OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR,
                         "Cannot find serializer implementation for "
                         "specified version",
                         "MeshSerializer::exportMesh" );
        }

        impl->exportMesh( pMesh, stream, endianMode );
    }
    //---------------------------------------------------------------------
    void MeshSerializer::importMesh( DataStreamPtr &stream, Mesh *pDest )
    {
        determineEndianness( stream );

        // Read header and determine the version
        unsigned short headerID;

        // Read header ID
        readShorts( stream, &headerID, 1 );

        if( headerID != HEADER_CHUNK_ID )
        {
            OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR, "File header not found",
                         "MeshSerializer::importMesh" );
        }
        // Read version
        String ver = readString( stream );
        // Jump back to start
        stream->seek( 0 );

        // Find the implementation to use
        MeshSerializerImpl *impl = 0;
        for( MeshVersionDataList::iterator i = mVersionData.begin(); i != mVersionData.end(); ++i )
        {
            if( ( *i )->versionString == ver )
            {
                impl = ( *i )->impl;
                break;
            }
        }
        if( !impl )
        {
            OGRE_EXCEPT( Exception::ERR_INTERNAL_ERROR,
                         "Cannot find serializer implementation for "
                         "mesh version " +
                             ver,
                         "MeshSerializer::importMesh" );
        }

        // Call implementation
        impl->importMesh( stream, pDest, mListener );
        // Warn on old version of mesh
        if( ver != mVersionData[0]->versionString )
        {
            LogManager::getSingleton().logMessage(
                "WARNING: " + pDest->getName() + " is an older format (" + ver +
                    "); you should upgrade it as soon as possible" + " using the OgreMeshTool tool.",
                LML_CRITICAL );
        }

        if( mListener )
            mListener->processMeshCompleted( pDest );
    }
    //---------------------------------------------------------------------
    void MeshSerializer::setListener( MeshSerializerListener *listener ) { mListener = listener; }
    //-------------------------------------------------------------------------
    MeshSerializerListener *MeshSerializer::getListener() { return mListener; }
}  // namespace Ogre
