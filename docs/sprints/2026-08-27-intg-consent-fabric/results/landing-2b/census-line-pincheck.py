import sys,hashlib
p=sys.argv[1]; L=open(p).read().split("\n")
PRE="bash docs/sprints/2026-08-27-intg-consent-fabric/results/landing-2b/intg-2b-landing-census.sh"; PIN="af8c1927462f5e40cf775419ae6c1d3070ba9e7fa1713248f9f7d50b42b7b3ad"
m=[x.strip()[1:-1] for x in L if x.strip().startswith("`"+PRE) and x.strip().endswith("`")]
if len(m)!=1: print("STOP census-line-count-%d"%len(m)); sys.exit(1)
if hashlib.sha256(m[0].encode()).hexdigest()!=PIN: print("STOP census-line-digest"); sys.exit(1)
print("census-line-pin-ok"); sys.exit(0)
