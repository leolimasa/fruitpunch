
/*
 * Raw.h
 *
 *  Created on: 2012-06-22
 *      Author: leo
 */

#ifndef RAW_H_
#define RAW_H_

#include <boost/shared_ptr.hpp>
#include <vector>
#include <fruitpunch/Resources/Resource.h>

namespace fp_core {

/// Reads and writes stream of bytes into a file.
/**
 * There are no modifications to the byte stream. It is read and written
 * exactly how it is on the file or buffer.
 */
class Raw : public Resource {
public:
  typedef boost::shared_ptr<Raw> ref;

  Raw();
  Raw(std::string filepath);
  virtual void load(std::string fullPath);
  void save(std::string fullPath);

  // --------------------------------------------------------------------------
  // Getters and setters
  // --------------------------------------------------------------------------
  boost::shared_ptr<std::vector<unsigned char> > getData() const;
  void setData(boost::shared_ptr<std::vector<unsigned char> > data);

private:
  boost::shared_ptr<std::vector<unsigned char> > mData;
};

}

#endif
