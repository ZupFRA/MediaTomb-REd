/*MT*
    
    MediaTomb - http://www.mediatomb.cc/
    
    cached_url.cc - this file is part of MediaTomb.
    
    Copyright (C) 2005 Gena Batyan <bgeradz@mediatomb.cc>,
                       Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>
    
    Copyright (C) 2006-2010 Gena Batyan <bgeradz@mediatomb.cc>,
                            Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>,
                            Leonhard Wimmer <leo@mediatomb.cc>
    
    MediaTomb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2
    as published by the Free Software Foundation.
    
    MediaTomb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    version 2 along with MediaTomb; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
    
    $Id: cached_url.cc 2081 2010-03-23 20:18:00Z lww $
*/

/// \file cached_url.cc

#ifdef HAVE_CONFIG_H
    #include "autoconfig.h"
#endif

#include <time.h>

#include "cached_url.h"
#include "tools.h"

using namespace zmm;

CachedURL::CachedURL(int object_id, zmm::String url)
{
    this->object_id = object_id;
    this->url = url;
    this->creation_time = time(NULL);
    if (this->creation_time == -1)
    {
        throw _Exception(_("Failed to get current time: ") + 
                         mt_strerror(errno));
    }
    this->last_access_time = creation_time;
    mutex = Ref<Mutex>(new Mutex(false)); // non recursive mutex
}

int CachedURL::getObjectID()
{
    return object_id;
}
    
String CachedURL::getURL()
{
    AUTOLOCK(mutex);
    last_access_time = time(NULL);
    if (last_access_time == -1)
    {
        throw _Exception(_("Failed to get current time: ") + 
                         mt_strerror(errno));
    }
    return url;
}
    
time_t CachedURL::getCreationTime()
{
    return creation_time;
}

    /// \brief Retrieves the time when the last access time of the data.
time_t CachedURL::getLastAccessTime()
{
    AUTOLOCK(mutex);
    return last_access_time;
}
