// -*- C++ -*-
// $Id$

#ifndef ZEROCOPYSEQ_H
#define ZEROCOPYSEQ_H

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include /**/ "ace/pre.h"

#include "dds/DCPS/ZeroCopySeqBase.h"
#include "dds/DCPS/ZeroCopyAllocator_T.h"
#include <ace/Vector_T.h>


namespace TAO
{
  namespace DCPS
  {


    class DataReaderImpl;
    class ReceivedDataElement;

    /**
    * Provides [] operators returning sample references
    *     but it is is implemented as
    *     an "array" of pointers to the samples so they can be
    *     "loaned" to the application code.
    *
    * Design Goals:
    *  - Provide enhanced performance known as "zero-copy" in the DDS spec
    *  - Conform to the C++ CORBA mapping for sequences
    *    - When necessary, certain uncommon sequence operations (resize,
    *      get_buffer, replace) will cause copies.  Performance impacts are
    *      noted in comments on the individual methods.
    */
    template <class Sample_T, size_t DEF_MAX = DCPS_ZERO_COPY_SEQ_DEFAULT_SIZE>
    class ZeroCopyDataSeq
    {
    public:

      /**
      * Construct a sequence of sample data values that supports
      * zero-copy reads.
      *
      * @param maximum Maximum number of samples to insert into the sequence.
      *                If == 0 then use zero-copy reading.
      *                Defaults to zero hence supporting zero-copy reads/takes.
      *
      * @param init_size Initial size of the underlying array of pointers.
      *
      * @param alloc The allocator used to allocate the array of pointers
      *              to samples. If zero then use the default allocator.
      *
      * This constructor also serves as the "maximum" ctor and default ctor
      * in the CORBA spec.
      */
      explicit ZeroCopyDataSeq(CORBA::ULong maximum = 0,
        CORBA::ULong init_size = DEF_MAX, ACE_Allocator* alloc = 0);

      ZeroCopyDataSeq(CORBA::ULong maximum, CORBA::ULong length,
        Sample_T* buffer, CORBA::Boolean release = false);

      ZeroCopyDataSeq(const ZeroCopyDataSeq& frm);

      ZeroCopyDataSeq& operator=(const ZeroCopyDataSeq& frm);

      void swap(ZeroCopyDataSeq& frm);

      ~ZeroCopyDataSeq();

      CORBA::ULong maximum() const;

      /** Performance note: increasing the length of a zero-copy sequence past
       *  its current length will cause a copy (the sequence will no longer be
       *  zero-copy enabled).
       */
      void length(CORBA::ULong length);
      CORBA::ULong length() const;

      const Sample_T& operator[](CORBA::ULong i) const;
      Sample_T& operator[](CORBA::ULong i);

      CORBA::Boolean release() const;

      void replace(CORBA::ULong max, CORBA::ULong length, Sample_T* buffer,
        CORBA::Boolean release = false);

      Sample_T* get_buffer(CORBA::Boolean orphan = false);
      const Sample_T* get_buffer() const;

      static Sample_T* allocbuf(CORBA::ULong nelems);
      static void freebuf(Sample_T* buffer);

      ///Only used by the FooDataReaderImpl and tests
      class PrivateMemberAccess
      {
      public:
        PrivateMemberAccess(ZeroCopyDataSeq& seq)
          : seq_(seq) {}

        CORBA::ULong max_slots() const { return seq_.max_slots(); }

        void internal_set_length(CORBA::ULong len)
        { seq_.internal_set_length(len); }

        void set_loaner(TAO::DCPS::DataReaderImpl* loaner)
        { seq_.set_loaner(loaner); }

        void assign_ptr(CORBA::ULong ii, TAO::DCPS::ReceivedDataElement* item)
        { seq_.assign_ptr(ii, item); }

        TAO::DCPS::ReceivedDataElement* get_ptr(CORBA::ULong ii) const
        { return seq_.get_ptr(ii); }

        void assign_sample(CORBA::ULong ii, const Sample_T& sample)
        { seq_.assign_sample(ii, sample); }

      private:
        ZeroCopyDataSeq& seq_;
      };
      friend class PrivateMemberAccess;

    private:

      /** ACE_Vector doesn't have a working swap()
        * function, so we have to provide our own.
        */
      class DDS_Vector
        : public ACE_Vector<TAO::DCPS::ReceivedDataElement*, DEF_MAX>
      {
      public:
        DDS_Vector(const size_t init_size = DEF_MAX, ACE_Allocator* alloc = 0);

        void swap(DDS_Vector&);

        using ACE_Vector::allocator_;
        using ACE_Vector::array_;
      };


      /**
      * Current allocated number of sample slots.
      *
      * @note The DDS specification's use of maximum=0 to designate
      *       zero-copy read request requires some
      *       way of knowing the internally allocated slots
      *       for sample pointers that is not "maximum".
      */
      CORBA::ULong max_slots() const;

      void internal_set_length(CORBA::ULong len);

      void set_loaner(TAO::DCPS::DataReaderImpl* loaner);

      void assign_ptr(CORBA::ULong ii, TAO::DCPS::ReceivedDataElement* item);

      TAO::DCPS::ReceivedDataElement* get_ptr(CORBA::ULong ii) const;

      void assign_sample(CORBA::ULong ii, const Sample_T& sample);

      bool is_zero_copy() const;

      void make_single_copy(CORBA::ULong maximum);

      /// The datareader that loaned its samples.
      TAO::DCPS::DataReaderImpl* loaner_;

      /// the default allocator
      FirstTimeFastAllocator<TAO::DCPS::ReceivedDataElement*, DEF_MAX>
        default_allocator_;

      typedef DDS_Vector Ptr_Seq_Type;

      /// array of pointers if the sequence is supporting zero-copy reads
      Ptr_Seq_Type ptrs_;

      //single-copy (aka non-zero-copy) support
      CORBA::ULong sc_maximum_;
      CORBA::ULong sc_length_;
      mutable Sample_T* sc_buffer_;
      mutable CORBA::Boolean sc_release_;

    }; // class ZeroCopyDataSeq

  } // namespace  ::DDS
} // namespace TAO

#if defined (__ACE_INLINE__)
#include "dds/DCPS/ZeroCopySeq_T.inl"
#endif /* __ACE_INLINE__ */

#if defined (ACE_TEMPLATES_REQUIRE_SOURCE)
#include "dds/DCPS/ZeroCopySeq_T.cpp"
#endif /* ACE_TEMPLATES_REQUIRE_SOURCE */

#if defined (ACE_TEMPLATES_REQUIRE_PRAGMA)
#pragma message ("ZeroCopySeq_T.cpp template inst")
#pragma implementation ("ZeroCopySeq_T.cpp")
#endif /* ACE_TEMPLATES_REQUIRE_PRAGMA */

#include /**/ "ace/post.h"

#endif /* ZEROCOPYSEQ_H  */
