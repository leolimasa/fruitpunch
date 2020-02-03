/*
 * ResourceFactory.cpp
 *
 *  Created on: 2012-06-10
 *      Author: leo
 */

#include <fruitpunch/Resources/ResourceFactory.hpp>
#include <fruitpunch/Common/Runtime.h>
#include <fruitpunch/Errors/ResourceLoadError.h>
#include <fruitpunch/Common/Observer.h>


using namespace std;
using namespace fp_core::common;

namespace fp_core {

ResourceFactory::ResourceFactory() {
  // TODO Auto-generated constructor stub

}

//______________________________________________________________________________

boost::shared_ptr<Resource> ResourceFactory::loadResource(std::string path) {
  // resolves the path
  path = Runtime::getCurrent()->resolve(path);

  // checks if we have an error while resolving the path
  if (path == "") {
    return boost::shared_ptr<Resource>();
  }

  // strips the file extension
   string extension = path.substr(path.find_last_of('.')+1);

   // converts the extension to lowercase
   std::transform( extension.begin(), extension.end(), extension.begin(),
   ::tolower );

   // finds a resource for the extension
   map<string, boost::shared_ptr<IFileExtension> >::iterator resourceIterator;
   resourceIterator = mExtensions.find(extension);

   // we couldn't find a handler for this resource
   if (resourceIterator == mExtensions.end()) {
     boost::shared_ptr<ResourceLoadError> error(new ResourceLoadError(extension, path));
     Runtime::getCurrent()->addError(error);
     return boost::shared_ptr<Resource>();
   }

   boost::shared_ptr<IFileExtension> fileExt = resourceIterator->second;
   boost::shared_ptr<Resource> resource = fileExt->createResource(path);
   return resource;
}

//______________________________________________________________________________

} /* namespace fp_core */
