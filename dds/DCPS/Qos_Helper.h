/*
 * $Id$
 *
 * Copyright 2010 Object Computing, Inc.
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#ifndef OPENDDS_DCPS_QOS_HELPER_H
#define OPENDDS_DCPS_QOS_HELPER_H

#include "dds/DdsDcpsC.h"
#include "ace/OS_NS_sys_time.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

// Define a macro since we should NOT declare methods as extern and
// then define them as inline
#if defined(__ACE_INLINE__)
# define EXTERN_OR_INLINE_HELPER_METHOD ACE_INLINE
#else
# define EXTERN_OR_INLINE_HELPER_METHOD
#endif

namespace OpenDDS {
namespace DCPS {

class Service_Participant;

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
ACE_Time_Value time_to_time_value(const DDS::Time_t& t);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
DDS::Time_t time_value_to_time(const ACE_Time_Value& tv);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
ACE_Time_Value duration_to_time_value(const DDS::Duration_t& t);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
ACE_Time_Value duration_to_absolute_time_value(const DDS::Duration_t& t,
                                               const ACE_Time_Value now = ACE_OS::gettimeofday());

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
DDS::Duration_t time_value_to_duration(const ACE_Time_Value& tv);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
DDS::Duration_t time_to_duration(const DDS::Time_t& t);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
CORBA::Long get_instance_sample_list_depth(
  DDS::HistoryQosPolicyKind history,
  long                        history_depth,
  long                        max_samples_per_instance);

/// Validate DDS::Duration_t value (infinite or positive and
/// non-zero).
EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool valid_duration(DDS::Duration_t const & t);

/// Check if given duration is either infinite or greater than or
/// equal to zero.
EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool non_negative_duration(DDS::Duration_t const & t);

/**
 * @class Qos_Helper
 *
 * @brief This class implements methods that verify whether a qos is
 *        valid, consistent and changeable.
 *
 * valid - the values are in acceptable ranges without respect
 *         to any other values.
 *
 * consistent - the values are consistent with each other.
 *         The spec sometimes calls this "compatible" but I
 *         this compatible should be reserved for matching
 *         QoS of subscriptions and publications.
 *         The spec is confusing in its inconsistency of the
 *         use of "compatible" and "consistent".
 *
 * The qos supported in current implementation:
 *         Liveliness  :   kind = AUTOMATIC
 *         Reliability :   kind = RELIABLE | BEST_EFFORT
 *                         max_blocking_time
 *         History     :   kind = KEEP_ALL | KEEP_LAST
 *                         depth > 1
 *         RESOURCE_LIMITS : max_samples_per_instance
 *
 * Other than these supported qos, any qos that is different from the
 * initial value is invalid.
 *
 * @note Since in the first implemenation of DSS in TAO a limited
 *       number of QoS values are allowed to be modified, the
 *       consistency test on QoS settings have not been
 *       implemented to check future "valid" QoS values.
 *
 * @note None of the supported QoS in the first implemenation are
 *       changeable. The changed value will be checked per the QoS
 *       table in the DDS specification.
 */
class OpenDDS_Dcps_Export Qos_Helper {
public:

  static bool consistent(
    DDS::ResourceLimitsQosPolicy const & resource_limits,
    DDS::HistoryQosPolicy const & history);

  static bool consistent(
    DDS::DeadlineQosPolicy const & deadline,
    DDS::TimeBasedFilterQosPolicy const & time_based_filter);

  static bool consistent(const DDS::DomainParticipantQos& qos);

  static bool consistent(const DDS::TopicQos& qos);

  static bool consistent(const DDS::DataWriterQos& qos);

  static bool consistent(const DDS::PublisherQos& qos);

  static bool consistent(const DDS::DataReaderQos& qos);

  static bool consistent(const DDS::SubscriberQos& qos);

  static bool consistent(const DDS::DomainParticipantFactoryQos & qos);

  static bool valid(const DDS::UserDataQosPolicy& qos);

  static bool valid(const DDS::TopicDataQosPolicy & qos);

  static bool valid(const DDS::GroupDataQosPolicy& qos);

  static bool valid(const DDS::TransportPriorityQosPolicy& qos);

  static bool valid(const DDS::LifespanQosPolicy& qos);

  static bool valid(const DDS::DurabilityQosPolicy& qos);

  static bool valid(const DDS::DurabilityServiceQosPolicy& qos);

  static bool valid(const DDS::PresentationQosPolicy& qos);

  static bool valid(const DDS::DeadlineQosPolicy& qos);

  static bool valid(const DDS::LatencyBudgetQosPolicy& qos);

  static bool valid(const DDS::OwnershipQosPolicy& qos);

  static bool valid(const DDS::OwnershipStrengthQosPolicy& qos);

  static bool valid(const DDS::LivelinessQosPolicy& qos);

  static bool valid(const DDS::TimeBasedFilterQosPolicy& qos);

  static bool valid(const DDS::PartitionQosPolicy& qos);

  static bool valid(const DDS::ReliabilityQosPolicy& qos);

  static bool valid(const DDS::DestinationOrderQosPolicy& qos);

  static bool valid(const DDS::HistoryQosPolicy& qos);

  static bool valid(const DDS::ResourceLimitsQosPolicy& qos);

  static bool valid(const DDS::EntityFactoryQosPolicy& qos);

  static bool valid(const DDS::WriterDataLifecycleQosPolicy& qos);

  static bool valid(const DDS::ReaderDataLifecycleQosPolicy& qos);

  static bool valid(const DDS::DomainParticipantQos& qos);

  static bool valid(const DDS::TopicQos& qos);

  static bool valid(const DDS::DataWriterQos& qos);

  static bool valid(const DDS::PublisherQos& qos);

  static bool valid(const DDS::DataReaderQos& qos);

  static bool valid(const DDS::SubscriberQos& qos);

  static bool valid(const DDS::DomainParticipantFactoryQos& qos);

  static bool changeable(const DDS::UserDataQosPolicy& qos1,
                         const DDS::UserDataQosPolicy& qos2);

  static bool changeable(const DDS::TopicDataQosPolicy & qos1,
                         const DDS::TopicDataQosPolicy & qos2);

  static bool changeable(const DDS::GroupDataQosPolicy& qos1,
                         const DDS::GroupDataQosPolicy& qos2);

  static bool changeable(const DDS::TransportPriorityQosPolicy& qos1,
                         const DDS::TransportPriorityQosPolicy& qos2);

  static bool changeable(const DDS::LifespanQosPolicy& qos1,
                         const DDS::LifespanQosPolicy& qos2);

  static bool changeable(const DDS::DurabilityQosPolicy& qos1,
                         const DDS::DurabilityQosPolicy& qos2);

  static bool changeable(const DDS::DurabilityServiceQosPolicy& qos1,
                         const DDS::DurabilityServiceQosPolicy& qos2);

  static bool changeable(const DDS::PresentationQosPolicy& qos1,
                         const DDS::PresentationQosPolicy& qos2);

  static bool changeable(const DDS::DeadlineQosPolicy& qos1,
                         const DDS::DeadlineQosPolicy& qos2);

  static bool changeable(const DDS::LatencyBudgetQosPolicy& qos1,
                         const DDS::LatencyBudgetQosPolicy& qos2);

  static bool changeable(const DDS::OwnershipQosPolicy& qos1,
                         const DDS::OwnershipQosPolicy& qos2);

  static bool changeable(const DDS::OwnershipStrengthQosPolicy& qos1,
                         const DDS::OwnershipStrengthQosPolicy& qos2);

  static bool changeable(const DDS::LivelinessQosPolicy& qos1,
                         const DDS::LivelinessQosPolicy& qos2);

  static bool changeable(const DDS::TimeBasedFilterQosPolicy& qos1,
                         const DDS::TimeBasedFilterQosPolicy& qos2);

  static bool changeable(const DDS::PartitionQosPolicy& qos1,
                         const DDS::PartitionQosPolicy& qos2);

  static bool changeable(const DDS::ReliabilityQosPolicy& qos1,
                         const DDS::ReliabilityQosPolicy& qos2);

  static bool changeable(const DDS::DestinationOrderQosPolicy& qos1,
                         const DDS::DestinationOrderQosPolicy& qos2);

  static bool changeable(const DDS::HistoryQosPolicy& qos1,
                         const DDS::HistoryQosPolicy& qos2);

  static bool changeable(const DDS::ResourceLimitsQosPolicy& qos1,
                         const DDS::ResourceLimitsQosPolicy& qos2);

  static bool changeable(const DDS::EntityFactoryQosPolicy& qos1,
                         const DDS::EntityFactoryQosPolicy& qos2) ;

  static bool changeable(const DDS::WriterDataLifecycleQosPolicy& qos1,
                         const DDS::WriterDataLifecycleQosPolicy& qos2);

  static bool changeable(const DDS::ReaderDataLifecycleQosPolicy& qos1,
                         const DDS::ReaderDataLifecycleQosPolicy& qos2);

  static bool changeable(const DDS::DomainParticipantQos& qos1,
                         const DDS::DomainParticipantQos& qos2);

  static bool changeable(const DDS::TopicQos& qos1,
                         const DDS::TopicQos& qos2);

  static bool changeable(const DDS::DataWriterQos& qos1,
                         const DDS::DataWriterQos& qos2);

  static bool changeable(const DDS::PublisherQos& qos1,
                         const DDS::PublisherQos& qos2);

  static bool changeable(const DDS::DataReaderQos& qos1,
                         const DDS::DataReaderQos& qos2);

  static bool changeable(const DDS::SubscriberQos& qos1,
                         const DDS::SubscriberQos& qos2);

  static bool changeable(const DDS::DomainParticipantFactoryQos& qos1,
                         const DDS::DomainParticipantFactoryQos& qos2);
};

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator== (const DDS::Duration_t& t1,
                 const DDS::Duration_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator!= (const DDS::Duration_t& t1,
                 const DDS::Duration_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator<(const DDS::Duration_t& t1,
                const DDS::Duration_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator<= (const DDS::Duration_t& t1,
                 const DDS::Duration_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator> (const DDS::Duration_t& t1,
                const DDS::Duration_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator>= (const DDS::Duration_t& t1,
                 const DDS::Duration_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator!(const DDS::Time_t& t);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator==(const DDS::Time_t& t1, const DDS::Time_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator!=(const DDS::Time_t& t1, const DDS::Time_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator<(const DDS::Time_t& t1, const DDS::Time_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator<=(const DDS::Time_t& t1, const DDS::Time_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator>(const DDS::Time_t& t1, const DDS::Time_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator>=(const DDS::Time_t& t1, const DDS::Time_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
DDS::Time_t operator-(const DDS::Time_t& t1, const DDS::Time_t& t2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::UserDataQosPolicy& qos1,
                  const DDS::UserDataQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::TopicDataQosPolicy & qos1,
                  const DDS::TopicDataQosPolicy & qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::GroupDataQosPolicy& qos1,
                  const DDS::GroupDataQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::TransportPriorityQosPolicy& qos1,
                  const DDS::TransportPriorityQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::LifespanQosPolicy& qos1,
                  const DDS::LifespanQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::DurabilityQosPolicy& qos1,
                  const DDS::DurabilityQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::DurabilityServiceQosPolicy& qos1,
                  const DDS::DurabilityServiceQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::PresentationQosPolicy& qos1,
                  const DDS::PresentationQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::DeadlineQosPolicy& qos1,
                  const DDS::DeadlineQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::LatencyBudgetQosPolicy& qos1,
                  const DDS::LatencyBudgetQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::OwnershipQosPolicy& qos1,
                  const DDS::OwnershipQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::OwnershipStrengthQosPolicy& qos1,
                  const DDS::OwnershipStrengthQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::LivelinessQosPolicy& qos1,
                  const DDS::LivelinessQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::TimeBasedFilterQosPolicy& qos1,
                  const DDS::TimeBasedFilterQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::PartitionQosPolicy& qos1,
                  const DDS::PartitionQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::ReliabilityQosPolicy& qos1,
                  const DDS::ReliabilityQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::DestinationOrderQosPolicy& qos1,
                  const DDS::DestinationOrderQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::HistoryQosPolicy& qos1,
                  const DDS::HistoryQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::ResourceLimitsQosPolicy& qos1,
                  const DDS::ResourceLimitsQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::EntityFactoryQosPolicy& qos1,
                  const DDS::EntityFactoryQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::WriterDataLifecycleQosPolicy& qos1,
                  const DDS::WriterDataLifecycleQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::ReaderDataLifecycleQosPolicy& qos1,
                  const DDS::ReaderDataLifecycleQosPolicy& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::DomainParticipantQos& qos1,
                  const DDS::DomainParticipantQos& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::TopicQos& qos1,
                  const DDS::TopicQos& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::DataWriterQos& qos1,
                  const DDS::DataWriterQos& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::PublisherQos& qos1,
                  const DDS::PublisherQos& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::DataReaderQos& qos1,
                  const DDS::DataReaderQos& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::SubscriberQos& qos1,
                  const DDS::SubscriberQos& qos2);

EXTERN_OR_INLINE_HELPER_METHOD OpenDDS_Dcps_Export
bool operator == (const DDS::DomainParticipantFactoryQos& qos1,
                  const DDS::DomainParticipantFactoryQos& qos2);

} // namespace DCPS
} // namespace OpenDDS


#if defined(__ACE_INLINE__)
#include "Qos_Helper.inl"
#endif /* __ACE_INLINE__ */

#endif /* OPENDDS_DCPS_QOS_HELPER_H */
