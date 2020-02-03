/*
 * ResourceFactory.h
 *
 *  Created on: 2012-06-10
 *      Author: leo
 */

#ifndef RESOURCEFACTORY_H_
#define RESOURCEFACTORY_H_

#include <fruitpunch/Resources/Resource.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <map>

namespace fp_core {

/**
 * Allows clients to associate file extensions with Resource classes, and
 * automatically instantiate those classes by just providing a file path.
 */
class ResourceFactory {
public:

  /**
   * Interface. Allows storing Resource types under the mExtensions map
   * in the ResourceFactory. We need to separate the Interface from the
   * implementation so that we can store it inside a map.
   * @return
   */
  class IFileExtension {
  public:
    virtual boost::shared_ptr<Resource> createResource(std::string fullPath) =0;
  };

  /// Implementation of the class above.
  template <typename RES>
  class FileExtension : public IFileExtension {

    virtual boost::shared_ptr<Resource> createResource(std::string fullPath) {
      
      boost::shared_ptr<Resource> res(new RES);
      res->load(fullPath);
      return res;
    }
  };

  ResourceFactory();

  /// Associates a resource with a file extension
  /**
   * This has to be defined in the header file because it uses a function
   * template.
   *
   * @param extension
   */
  template <typename RES>
  void associate(std::string extension) {
    using namespace std;
    using namespace boost;

    boost::shared_ptr<IFileExtension> ext(new FileExtension<RES>());
    mExtensions.insert(pair<string, boost::shared_ptr<IFileExtension> >(extension, ext));
  }


  /// Returns a loaded resource automatically detected by the file extension
  /**
   * This will automatically detect which resource is associated to the
   * file extension provided in the path, and return a new instance of the
   * resource. It will automatically call the load() method of the resource.
   *
   * @param path
   * @return
   */
  boost::shared_ptr<Resource> loadResource(std::string path);

private:
  std::string mRoot;
  std::map<std::string, boost::shared_ptr<IFileExtension> > mExtensions;
};

}
 /* namespace fp_core */
#endif /* RESOURCEFACTORY_H_ */
